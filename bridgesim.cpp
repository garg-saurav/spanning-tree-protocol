#include "bridgesim.h"

using namespace std;

void simulate(vector<Bridge>& bridges, map<char, vector<int> >& lan_to_bridgeIds, int trace){

	int time=0;
	int n=bridges.size();
	bool change=true;

	vector<vector<int> > conf_messages(n,vector<int>(3));

	while(change==true){
		change=false;
		
		for(int i=0; i<n; i++){
			bridges[i].get(conf_messages[i]);
		}
		
		for(int i=0; i<n; i++){
			if(trace==1)
				cout<<time<<" s B"<<i+1<<" (B"<<conf_messages[i][0]+1<<", "<<conf_messages[i][1]<<", B"<<conf_messages[i][2]+1<<")"<<endl;
		}
		
		time++;

		for(int i=0; i<n; i++){
			for(auto it=bridges[i].lans.begin(); it!=bridges[i].lans.end(); it++){
				if(it->second==NP){continue;}
				if(it->second==RP){continue;}
				for(auto it1=lan_to_bridgeIds[it->first].begin(); it1!=lan_to_bridgeIds[it->first].end(); it1++){	
					if(*it1==i){continue;}
					if (trace==1)
						cout<<time<<" r B"<<*it1+1<<" (B"<<conf_messages[i][0]+1<<", "<<conf_messages[i][1]<<", B"<<conf_messages[i][2]+1<<")\n";
					bool res=bridges[*it1].receive(conf_messages[i][0],conf_messages[i][1],conf_messages[i][2],it->first);
					change=change or res;
				}
			}
		}		
	}

	for(int i=0;i<n; i++){
		cout<<"B"<<i+1<<":";
		for(auto it=bridges[i].lans.begin(); it!=bridges[i].lans.end(); it++){
			switch(it->second) {
				case RP: cout<<" "<<it->first<<"-RP"; break;
				case DP: cout<<" "<<it->first<<"-DP"; break;
				case NP: cout<<" "<<it->first<<"-NP"; break;
				default: cout<<" "<<it->first<<"-INVALID"; break;

			}
		}
		cout<<"\n";
	}
}

void transfer_simulate(vector<Bridge>& bridges, map<char, vector<int> >& lan_to_bridgeIds, map<string,char>& host_to_lan, string host_src, string host_dst, int trace){
	char lan_port=host_to_lan[host_src];
	queue<pair<pair<int, char>, int> > bridgeIdsPorts;  // bridgeIds and Ports(receiving port) from where to transfer next at time t
	int time=0;
	for(auto i:lan_to_bridgeIds[lan_port]){
		if(bridges[i].lans[lan_port]!=NP)
			bridgeIdsPorts.push(make_pair(make_pair(i,lan_port), time));
	}

	while(!bridgeIdsPorts.empty()){
		pair<pair<int, char>, int> a=bridgeIdsPorts.front();
		pair<int, char> i=a.first;
		bridgeIdsPorts.pop();
		// if (trace==1)
		// 	cout<<time<<" s B"<<i.first<<" "<<
		vector<char> next_port=(bridges[i.first]).transfer(host_src,host_dst,i.second);
		for(auto i1:next_port){
			if(i1==i.second) continue;
			if (trace==1)
				cout<<a.second<<" s B"<<i.first+1<<" "<<i.second<<"-->"<<i1<<endl;
			for(auto j:lan_to_bridgeIds[i1]){
				if(j!=i.first && bridges[j].lans[i1]!=NP)
					bridgeIdsPorts.push(make_pair(make_pair(j,i1),a.second+1));
			}
		}
	}


	for(int i=0; i<bridges.size(); i++){
		cout<<"B"<<i+1<<":\n";
		cout<<"HOST ID | FORWARDING PORT\n";
		for(auto j:bridges[i].forwarding_table){
			cout<<j.first<<" | "<<j.second<<"\n";
		}
	}

	
	cout<<"\n";
}