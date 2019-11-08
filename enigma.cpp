#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

int inputToInteger(char c);

/* 
   Rotors are the main agents in Enigma encryption. They work as following:
   
   Based on a given wiring, it maps the input signal with an output signal. 
      *OBS: This signal usually flows through 3 to 4 rotors, that may have different wirings.
      *Hint: the wiring patterns are specified in rotor-wiring.txt, a file that contains 3+ models.

   Besides, everytime a key is pressed, the right-most rotor rotates, what creates an offset in the wiring pattern.
      *OBS: A rotor is simulated as a deque, what makes this operation more intuitive.

   When the right-most rotor performs a full spin, the rotor in its left rotates once. And the same goes for every rotors.
      *OBS: This is simulated by the function rotate().

   EXAMPLE:
      In a Enigma machine that is designed to support 3 rotors, let's call the right one A, the center one B, and the left-most one C.
      At every keypress, A performs a single spin.
      At every full spin of A (26 keypresses), B performs a single spin.
      This means that C spins once at every 676 keypresses.

*/
class Rotor
{
private:
      // Constructor elements. Rotors includes a type (a.k.a model), a wiring configuration (see wirings.txt) and an initial offset.
      string type;
      string wiring;
      int offset;
      int rotation_amount;

      deque<int> deque_wiring;

public:
      // Constructor method
      Rotor(string t, string w, int off)
      {
            type = t;
            wiring = w;
            offset = off;
            rotation_amount = 0;

            createDeque(wiring);
            applyOffset();
      }

      // Get type
      string getType()
      {
            return type;
      }

      // Get offset
      int getOffset()
      {
            return offset;
      }

      // Get deque
      deque<int> getDeque()
      {
            return deque_wiring;
      }

      // Set the type (also referenced as a model in this code) of the rotor, tipically a string.
      void setType(string s)
      {
            type = s;
      }

      // Set the initial offset of a rotor
      void setOffset(int off)
      {
            offset = off;
      }

      // Creates a deque, based on the given wiring. This is defined by the model of the rotor, and can be analyzed with Rotor class getters, or in wirings.txt.
      void createDeque(string s)
      {
            for (int i = 0; i < s.length(); i++)
            {
                  deque_wiring.push_back(s[i]);
            }
      }

      // Applies the initial offset to the queue. This is equivalent to configuring the initial position of a rotor on a real Enigma machine.
      void applyOffset()
      {
            for (int i = 0; i < offset; i++)
            {
                  deque_wiring.push_front(deque_wiring.back());
                  deque_wiring.pop_back();
            }
      }

      // Simulates a rotation of the rotor
      int rotate()
      {
            char deque_back = deque_wiring.back();
            deque_wiring.pop_back();
            deque_wiring.push_front(deque_back);

            int flag_full_turn = 0;

            if (rotation_amount == 25)
            {
                  rotation_amount = 0;
                  flag_full_turn = 1;
            }
            else
                  rotation_amount++;

            return flag_full_turn;
      }
};

class Reflector
{
private:
      // Constructor elements. Rotors includes a type (a.k.a model), a wiring configuration (see wirings.txt) and an initial offset.
      string type;
      string wiring;

public:
      Reflector(string t, string w)
      {
            type = t;
            wiring = w;
      }

      char reflect(char input_c)
      {
            char output_c = wiring[inputToInteger(input_c) - 1];

            return output_c;
      }
};

// Enigma class
class Enigma
{
private:
      // An enigma include a set of rotors.
      vector<Rotor> rotors;
      Reflector reflector;

public:
      Enigma(vector<Rotor> v, Reflector r) : rotors(v), reflector(r) {}

      vector<Rotor> getRotors()
      {
            return rotors;
      }

      Rotor getSingleRotor(int pos)
      {
            return rotors[pos];
      }

      int encrypt(int code)
      {
            code = signal_flow(code, 1);

            code = reflector.reflect(code);

            code = signal_flow(code, 2);

            int idx = 0; // Variable that stores a temporary counter.

            // Whenever a char is pressed, rotates the first rotor, before the encryption is made.
            int flag_full_turn = rotors[idx].rotate();

            // Perform the full rotation of rotors, whenever flag_full_turn is activated
            while (flag_full_turn == 1 && idx < rotors.size())
            {
                  idx++;
                  flag_full_turn = rotors[idx].rotate();
            }

            return code;
      }

      // This functions sends the input signal through the rotors.
      int signal_flow(int code, int mode)
      {
            vector<Rotor> rotors_list = rotors;

            if (mode == 2)
            {
                  reverse(rotors_list.begin(), rotors_list.end());
            }

            for (int i = 0; i < rotors_list.size(); i++)
            {
                  Rotor current_rotor = rotors_list[i];

                  deque<int> current_rotor_wiring = current_rotor.getDeque();

                  if (mode == 1)
                        code = current_rotor_wiring.at(inputToInteger(code) - 1);
                  else if (mode == 2)
                  {
                        for (int i = 0; i < 26; i++)
                        {
                              if (current_rotor_wiring.at(i) == code)
                              {
                                    // Converts the integer i to an upper letter.
                                    code = i + 65;
                                    break;
                              }
                        }
                  }
            }

            return code;
      }
};

// Gets user input, based on the index of the rotor to be scanned. TODO: Handle unsupported inputs.
int getInput(int index)
{
      int input;

      switch (index)
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

      // This pair is used as an auxiliar variable to store returns from searchRotor() function.
      pair<string, string> pair_model_wiring = searchRotor(idx_rotor);

      // Assign each variable stored in the pair to a specific string (Rule #1: ALWAYS use mnemonic variable names).
      string model = pair_model_wiring.first;
      string wiring = pair_model_wiring.second;

      // Scans the initial offset. TODO: Handle exceptions, and support both letters or numbers.
      int offset;

      // Scans the offset
      cout << "Set the initial offset for this rotor: ";
      cin >> offset;

      // Returns a tuple consisting off all the information needed to create a Rotor-type object.
      return make_tuple(model, wiring, offset);
}

pair<string, string> scanReflector(int index)
{
      int idx_reflector = index;

      pair<string, string> pair_model_wiring = searchReflector(idx_reflector);

      return pair_model_wiring;
}

/* 
   This function calls the procedure to scan the model of the desired rotor (passed as argument of this function). 
   Then, it generates a Rotor object with that info. 
*/
Rotor createRotor(int index)
{
      // Receives a tuple with the following format <MODEL, WIRING, OFFSET>
      tuple<string, string, int> tuple = scanRotor(index);

      // Finally, creates an object and returns it.
      Rotor rotor(get<0>(tuple), get<1>(tuple), get<2>(tuple));

      return rotor;
}

Reflector createReflector(int index)
{
      pair<string, string> pair = scanReflector(index);

      Reflector reflector(pair.first, pair.second);

      return reflector;
}

// Sets an enigma machine. This is done by filling it slots (vector of Rotors -> dinamically allocated) with rotors.
Enigma setEnigma()
{
      // Creates all the 3 rotors. TODO: Setup a way to allow user to include any amount of rotors.
      Rotor right_rotor = createRotor(1);
      Rotor center_rotor = createRotor(2);
      Rotor left_rotor = createRotor(3);

      vector<Rotor> set_of_rotors{right_rotor, center_rotor, left_rotor};

      Reflector reflector = createReflector(1);

      Enigma enigma(set_of_rotors, reflector);

      return enigma;
}

// The implemented logic uses numbers to identify each letter (range 1-26). This function does a simple conversion between char and integer types, using ASCII codes.
int inputToInteger(char c)
{
      char lower_c = tolower(c);
      int code = lower_c - 96;

      return code;
}

void step()
{
      char input;

      while (true)
      {
      }
}

int main()
{
      int count = 1;

      string s;
      
      Enigma enigma = setEnigma();

      cout << endl;
      
      cout << "Type your text: ";
      std::getline(std::cin >> ws, s);

      // Check if Enigma class and its objects are working correctly.
      // cout << enigma.getSingleRotor(0).getType() << endl;

      //cout << count << ". " << c << " -> " << (char) enigma.encrypt(c) << endl;

      cout << endl;
      
      cout << "Encrypted text: ";

      s.erase(remove(s.begin(), s.end(), ' '), s.end());

      for(auto c : s)
      {
            cout << (char)enigma.encrypt(c);

            // Breaks encrypted text into sets of 4 letters;
            if(count % 4 == 0)
            cout << " ";

            count++;
      }

      cout << endl;

      return 0;
}