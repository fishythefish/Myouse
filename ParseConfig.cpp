#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

struct gestureMap{
  string name;
  string fist;
  string waveIn;
  string waveOut;
  string fingersSpread;
};

pair<string, string> parseConfLine(string line){
  pair<string, string> parsedLine;
  parsedLine.first = line.substr(0,line.find(' '));
  parsedLine.second = line.substr(line.find(' ') + 1, line.size());
  //cout << "first: " << parsedLine.first << "-";
  //cout << "second: " << parsedLine.second << endl;
  return parsedLine;
}

static vector<gestureMap> readConfig(){
  vector<gestureMap> gestureList;
  ifstream conf("gestures.conf");
  string line;
  pair<string, string> parsedLine;
  gestureMap currentGesture;
  bool created = false;
  while (!conf.eof() && getline(conf, line)){
    //cout << line << endl;
    if (line.size() > 0 && line.at(0) != '#' && line.at(0) >= 'A' && line.at(0) <= 'z' ){
      parsedLine = parseConfLine(line);
      if (!parsedLine.first.compare("name") && created){
        gestureList.push_back(currentGesture);
        //cout << "created gesture list" << endl;;
      }
      if (!parsedLine.first.compare("name")){
        //cout << "found name: " << parsedLine.second << endl;
        currentGesture.name = parsedLine.second;
        created = true;
      }
      else if (!parsedLine.first.compare("fist")){
        //cout << "found fist: " << parsedLine.second << endl;
        currentGesture.fist = parsedLine.second;
      }
      else if (!parsedLine.first.compare("waveIn")){
        //cout << "found waveIn: " << parsedLine.second << endl;
        currentGesture.waveIn = parsedLine.second;
      }
      else if (!parsedLine.first.compare("waveOut")){
        //cout << "found waveOut: " << parsedLine.second << endl;
        currentGesture.waveOut = parsedLine.second;
      }
      else if (!parsedLine.first.compare("fingersSpread")){
        //cout << "found fingersSpread: " << parsedLine.second << endl;
        currentGesture.fingersSpread = parsedLine.second;
      }
    }
  }
  gestureList.push_back(currentGesture);
  return gestureList;
}

/*
// Used for testing these functions
int main(){
  vector<gestureMap> gestures = readConfig();
  //cout << gestures.size() << endl;
  for (int i = 0; i < gestures.size(); i++){
    cout << gestures[i].name << " " << gestures[i].fist << " " << gestures[i].waveIn << " " << gestures[i].waveOut << " " << gestures[i].fingersSpread << endl;
  }
}
*/
