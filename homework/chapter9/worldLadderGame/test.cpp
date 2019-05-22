#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<map>

using namespace std;

map<string, string> findChain(const map<string, vector<string> > &adjcentWord, const string &start);
vector<string> getChain(const map<string, string> &previousWord, const string &target);

int main(){
	map<string, vector<string> > words;
	words.insert(pair<string, vector<string> >("zero", {"hero"}));
	words.insert(pair<string, vector<string> >("hero", {"zero", "here"}));
	words.insert(pair<string, vector<string> >("here", {"hero", "hire"}));
	words.insert(pair<string, vector<string> >("hire", {"here", "fire"}));
	words.insert(pair<string, vector<string> >("fire", {"hire", "five"}));
	words.insert(pair<string, vector<string> >("five", {"fire"}));
	auto previousWord = findChain(words, "zero");			//map<string, string> previousWord = findChain(words, "zero");
	auto result = getChain(previousWord, "five");			//vector<string> result = getChain(previousWord, "five");auto result = getChain(previousWord, "five");
	for(auto i:result){ 									//for(typename vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr){for(auto i:result){
		cout << i << " " ;									//cout << *itr << " ";											
	}
	cout << endl;
	return 0;
}

map<string, string> findChain(const map<string, vector<string> > &adjcentWord, const string &first){
	map<string, string> previousWord;
	queue<string> q;
	q.push(first);
	while(!q.empty()){
		string current = q.front();
		q.pop();
		auto itr = adjcentWord.find(current);						//map<string, vector<string> >::const_iterator itr = adjcentWord.find(current);
		const vector<string> &adjcent = itr -> second;
		for(string i:adjcent){										//for(int i = 0; i < adjcent.size(); i++){
			if(previousWord[i] == ""){								//if(previousWord[adjcent[i]] == ""){
				previousWord[i] = current;							//previousWord[adjcent[i]] = current;
				q.push(i);											//q.push(adjcent[i]);
			}
		}
	}
	previousWord[first] = "";
	return previousWord;
}

vector<string> getChain(const map<string, string> &previousWord, const string &target){
	vector<string> result;
	auto &prev = const_cast<map<string, string> &>(previousWord);	//map<string, string> &prev = const_cast<map<string, string> &>(previousWord);
	for(string current = target; current != ""; current = prev[current]){
		result.push_back(current);
	}
	reverse(result.begin(), result.end());
	return result;
}






