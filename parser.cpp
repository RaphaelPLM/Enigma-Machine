#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

// Extract both model and wirings of the rotor referenced in string s. This is done by splitting a given line into a model name, and its respective wirings.
pair<string, string> getFields(string s)
{
   string model = "";
   string wiring = "";

   for(auto c : s)
   {
      // The model and the wiring for each rotor are separated by a ":".
      if(c != ':')
         model += c;
      else
      {
         // Removes the model name and the two following characters ": " from s. The resultant string is the wiring for the rotor referenced by model.
         wiring = s.erase(0, model.length() + 2);
         
         break;
      }
   }

   pair<string, string> pair_model_wiring = make_pair(model, wiring);

   return pair_model_wiring;
}

pair<string, string> searchRotor(int rotor_index)
{
   map<int, string> map_rotorModels = 
   {
      {1, "ROTOR_I"},
      {2, "ROTOR_II"},
      {3, "ROTOR_III"}
   };
   
   //Allocate a file enabled for read-only
   ifstream f_rotor_wirings;
    
   //Open specified .GraphModellingLanguage file
   f_rotor_wirings.open("wirings.txt");

   if(!f_rotor_wirings)
   {
      cout << "Unable to read rotor wirings. Check if the file 'wirings.txt' exists.\n";
   }
 
   string line;
   
   pair<string, string> pair_model_wirings;

   while (getline(f_rotor_wirings, line))
   {
      pair_model_wirings = getFields(line);      

      if(pair_model_wirings.first == map_rotorModels[rotor_index])
         break;
   }

   return pair_model_wirings;  
}

