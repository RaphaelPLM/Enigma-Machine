#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

class Rotor
{
   private:
      // Constructor elements
      string type;
      string wiring;
      int offset;
      
      queue<int> queue_wiring;
   
   public:
      Rotor(string t, string w, int off)
      {
         type = t;
         wiring = w;
         offset = off;

         createQueue(wiring);
         applyOffset();
      }

      string getType()
      {
         return type;
      }

      int getOffset()
      {
         return offset;
      }

      // Set the type of the rotor, tipically a string
      void setType(string s)
      {
         type = s;
      }
      
      // Set the initial offset of a rotor
      void setOffset(int off)
      {
         offset = off; 
      }
      
      // Creates a queue, based on the given wiring. This is defined by the model of the rotor.
      void createQueue(string s)
      {
         for (int i = 0; i < s.length(); i++)
         {
            queue_wiring.push(s[i]);
         }  
      }

      // Applies the initial offset to the queue. This is equivalent to configuring the initial position of a rotor on a real Enigma machine.
      void applyOffset()
      {
         for (int i = 0; i < offset; i++)
         {
            char aux = queue_wiring.back();
            queue_wiring.pop();
            queue_wiring.push(aux);
         }
      }
};

int getInput(int index)
{
   int input;

   switch(index)
   {
      case 1:
         cout << "Set the model of the right rotor: ";
         break;
      case 2:
         cout << "Set the model of the center rotor: ";
         break;
      case 3:
         cout << "Set the model of the left rotor: ";
         break;
   }
   
   cin >> input;

   return input;
}

// Scans the rotor's model and wiring from the file "wirings.txt", and its initial offset.
tuple<string, string, int> scanRotor(int index)
{
   int idx_rotor = getInput(index);
   pair<string, string> pair_model_wiring = searchRotor(idx_rotor);


   string model = pair_model_wiring.first;
   string wiring = pair_model_wiring.second;
   int offset;
   
   // Scans the offset
   cout << "Set the initial offset for this rotor: ";
   cin >> offset;

   return make_tuple(model, wiring, offset);
}

Rotor createRotor(int index)
{
   tuple<string, string, int> tuple = scanRotor(index);
      
   Rotor rotor(get<0>(tuple), get<1>(tuple), get<2>(tuple));

   return rotor;
}

void step()
{
   char input;

}

int main()
{
   Rotor rotor = createRotor(1);
   cout << rotor.getType() << endl;
   cout << rotor.getOffset() << endl;
}