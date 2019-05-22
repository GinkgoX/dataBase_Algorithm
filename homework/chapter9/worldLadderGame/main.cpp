#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

//find the connection chain starting at start
map<string, string> findChain(const map<string, vector<string> > &adjcentWord, const string &start);

//get the chain with destreation as target
vector<string> getChain(const map<string, string> &previousWord, const string &target);

int main(){
	map<string, vector<string> > words;
	words.insert(pair<string, vector<string> >("zero", {"hero"}));
	words.insert(pair<string, vector<string> >("hero", {"zero", "here"}));
	words.insert(pair<string, vector<string> >("here", {"hero", "hire"}));
	words.insert(pair<string, vector<string> >("hire", {"here", "fire"}));
	words.insert(pair<string, vector<string> >("fire", {"hire", "five"}));
	words.insert(pair<string, vector<string> >("five", {"fire"}));
	map<string, string> previousWord = findChain(words, "zero");								//auto previousWord = findChain(words, "zero");
	vector<string> result = getChain(previousWord, "five");										//auto result = getChain(previousWord, "five");
	for(typename vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr){	//for(auto i:result){
		cout << *itr << " ";																	//cout << i << " " ; 
	}
	cout << endl;
	return 0;
}

map<string, string> findChain(const map<string, vector<string> > &adjcentWord, const string &key){
	map<string, string> previousWord;
	queue<string> q;
	//enqueue the start key
	q.push(key);
	while(!q.empty()){
		string current = q.front();
		q.pop();
		map<string, vector<string> >::const_iterator itr = adjcentWord.find(current);	//auto itr = adjcentWord.find(current);
		//get the map value : note map(first(key), second(value))
		const vector<string> &adjcent = itr -> second;
		for(int i = 0; i < adjcent.size(); i++){										//for(string i:adjcent){
			if(previousWord[adjcent[i]] == ""){
				previousWord[adjcent[i]] = current;
				q.push(adjcent[i]);
			}
		}
	}
	previousWord[key] = "";
	return previousWord;
}

vector<string> getChain(const map<string, string> &previousWord, const string &target){
	vector<string> result;
	//converet the const &previousWord to &prev : the map does not offer this convert
	map<string, string> &prev = const_cast<map<string, string> &>(previousWord);		//auto &prev = const_cast<map<string, string> &>(previousWord);
	for(string current = target; current != ""; current = prev[current]){
		result.push_back(current);
	}
	reverse(result.begin(), result.end());
	return result;
}






