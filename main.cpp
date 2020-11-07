#include "bridgesim.h"
#include<sstream>
#include<fstream>

using namespace std;

int main(int argc, char* argv[]){

	
	int trace;
	int no_of_bridges;
	vector<Bridge> bridges;
	map<char, vector<int> > lan_to_bridgeIds;
	string str;
	stringstream strValue;
	string bdg;
	int bdg_id;

	ifstream infile;
	infile.open("inp1");

	infile>>trace;
	infile>>no_of_bridges;
	infile.get(); // remove `\n` from input stream
	infile.get();

	for(int i=0; i<no_of_bridges; i++){  // reading bridges configuration
		vector<char> lans_list;
		getline(infile,str);
		if(str[str.size()-1]=='\r')
			str=str.substr(0,str.size()-1); // removing `\r`
		bdg=str.substr(0,str.find(' '));
		bdg=bdg.substr(1,bdg.size()-2); // removed character `B` and `:`
		strValue.clear();
		strValue << bdg;
		strValue >> bdg_id;
		bdg_id--; // 0 based indexing
		while(i!=bdg_id){
			lans_list=vector<char>();
			bridges.push_back(Bridge(i,lans_list));
			i++;
		}
		lans_list=vector<char>();
		for(auto x:str.substr(bdg.size()+3)){
			if(x!=' ' && x!='\n'){
				lans_list.push_back(x);
				lan_to_bridgeIds[x].push_back(i);
			}
		};
		bridges.push_back(Bridge(i,lans_list));
	}

	simulate(bridges, lan_to_bridgeIds, trace);

	/////////////////////////////////////transfers//////////////////////////////////

	map<string,char> host_to_lan;
	
	for(int i=0; i<lan_to_bridgeIds.size(); i++){ // reading hosts configuration
		getline(infile,str);
		string port=str.substr(0,str.find(' '));
		if(str[str.size()-1]=='\r')
			str=str.substr(0,str.size()-1);
		port=port.substr(0,port.size()-1); // removed character `:`
		strValue.clear();
		strValue << str.substr(3);
		string host;
		while(getline(strValue,host,' ')){
			host_to_lan[host]=port[0];
		}
	}

	int no_of_transfers;
	infile>>no_of_transfers;
	infile.get(); // remove `\n` from input stream
	infile.get();

	for(int i=0; i<no_of_transfers; i++){ // reading hosts configuration
		getline(infile,str);
		if(str[str.size()-1]=='\r')
			str=str.substr(0,str.size()-1);
		string host1=str.substr(0,str.find(' '));
		string host2=str.substr(str.find(' '));
		host2=host2.substr(1); // removing the space in beginning
		transfer_simulate(bridges,lan_to_bridgeIds,host_to_lan,host1,host2,trace);

	}	
	return 0;
}