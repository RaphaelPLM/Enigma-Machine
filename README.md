## About Enigma

The **Enigma Machine** is an encryption device used mainly during WWII. It also motivated the creation of the famous **Bombe** machine by Alan Turing and other researchers. 

## About the project

This project started as a programming exercise. After studying the engine of the Enigma, I decided to emulate its logic in a C++ program. 

Enigma logic could be easily simulated with just a few lines of code, but this project aims to implement its mechanisms close to the real machines. This means that some elements of the source code may seem inneficient, but the overall goal is to maintain low levels of abstraction.

## How to use

The enigma is a modular machine. This means that different **modules** (rotors and reflectors) can be attached in order to generate different patterns of encryption. 

These modules are specified in two files: 
  - wirings.txt (Rotors)
  - reflector_wiring.txt (Reflectors)
reflector
### 1. Setting up
The first step of the execution is to select three **rotors.** After selecting each rotor model, you'll be asked to select its **offset**. Then, you'll be prompted to select a **reflector**.

This process corresponds to the **configuration** step of a real Enigma. Rotors and a reflector will be inserted into the machine, and then the rotors will be rotated in order to generate an offset.

### 2. Encryption

After setting up the machine, you'll be able to write a sentence, and get its encrypted version. 
It's very important to **keep track of the adopted configuration** (the model of the reflectors, the three rotors and its offsets), because this is what guarantees that the decryption step will produce the right output.

### 3. Decryption

Currently, in order to decrypt a message, you need to restart the program :( Then, you have to setup the Enigma with the **same configuration** as in the encryption step. This means you have to select the same rotors in the same order, as well as the same offsets and reflector.

After setting it up, you just have to enter the encrypted message, and the original sentence will be then displayed.

## How to compile

Currently, the project has no Makefile. This means the following instruction must be executed to compile:
```sh
$ g++ enigma.cpp parser.cpp
```


