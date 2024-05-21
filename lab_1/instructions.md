# Lab 1 - RSA #
In this lab, you will accomplish two goals; sending RSA encrypted messages and decrypting a response and implementing a byte-wise RSA algorithm of your own. Messages will be handled using Linux's openssl package so that you can get some hands-experience handling the tools you'd likely be using in the real world. You are free to choose any language you'd like to create a code implementation of the algorithm.

This lab includes some code you will create. Please branch this repo using git's checkout.
```
git checkout -b YOUR_NAME
```
After completing the lab, please push your modifications to the repo on your branch.
```
git status (should say you are on the YOUR_NAME branch. If not get on your branch)
git add -A
git commit -m "your_commit_message"
git push origin main
```

# Table Of Contents #
- [Lab 1 - RSA](#lab-1---rsa)
- [Table Of Contents](#table-of-contents)
- [Part 1 - Communicating with Encrypted Messages](#part-1---communicating-with-encrypted-messages)
- [Part 2 - Creating Your Own RSA Encryption Program](#part-2---creating-your-own-rsa-encryption-program)
  - [Step 1: Pseudocode](#step-1-pseudocode)
    - [Pseudocode, What's That? (IMPORTANT)](#pseudocode-whats-that-important)
    - [Pseudocode Example](#pseudocode-example)
  - [Step 2: Code Time, Baby!](#step-2-code-time-baby)
    - [Recap - RSA Computations](#recap---rsa-computations)
    - [When You're Done](#when-youre-done)

# Part 1 - Communicating with Encrypted Messages #
For this first part, we will be simulating the communication between your employer's database and your provided work computer. Some of these files you are requesting to read are highly sensitive, so they are encrypted with RSA, the key for which was provided for you. By doing so, the database can keep its sensitive data encrypted using the public key, and then distribute a private key to the employee so that they can decrypt the requested information.

For reference, the command used to create the organization's public key is as follows.
```
openssl genrsa -out path/to/priv_file 2048
openssl rsa -pubout -in path/to/priv_file -pubout -out path/to/pub_file
```

In this series of commands, we first generate a new key pair for rsa-2048 encryption. Following this generation, the second command then extracts the public aspect of the key pair. In practice, a database admin could bind an rsa key pair to each employee so that when a user requess sensitive information they must first provide login credentials to then receive the encrypted files.

Given the appropriate private key (provided with this lab) a message can be decrypted with these commands.

```
openssl pkeyutl -decrypt -inkey path/to/key -in path/to/secret_file -out path/to/encrypted_file
```

NOTE: Any file following the -out flag does not need to exist. If it does not, it will be created.

Decrypt the file included in this lab and follow the resulting instructions.

# Part 2 - Creating Your Own RSA Encryption Program #
Now that you have communicated using encrypted data, it is benficial to build a script that encrypts information by hand. Accomplish this task in any language of choice :)

## Step 1: Pseudocode ##
Some of you will read this and be ready to run for the hills, and that's ok. Those same people (you know who you are) also create code that looks like you hate pseudocode, so this is me calling you out. Before we get started, lets demistify pseudocode.

### Pseudocode, What's That? (IMPORTANT) ###
Most simply, pseudocode is our way as programmers to storyboard the goals and logical blocks of our program. This is probably review for most of us, but I cannot understate its importance. By laying out the bones of our program before we get started, we will have a much more stable foundation.

### Pseudocode Example ###
In this case, lets pseudocode whether or not an integer between 1 and 100 is prime or not. Functions will be defined first, and our main function will describe the master process of the program.

```
define is_prime(integer) -> bool
    If a number can not be perfectly divided by 2, 3, 5, and 7,
    it is prime.

define main(void) -> void
    Prompt the user for a number

    If is_prime == true
        Reply "is prime"
    Else
        Reply "is not prime"
```

There are two important elements to pseudocode. First, we define all of our functions and include what data type(s) they take and return. Secondly, sectioned out and clear steps are written within each function so that the function's intentions/operations are obvious.

I will not tell you your pseudocode is bad, but it really will be benificial. If you do it, please include it along with the code you submit.

## Step 2: Code Time, Baby! ##

### Recap - RSA Computations ###
1. Define 2 primes p and q
2. Compute n and its totient
3. Select e and d from possible factors
4. Encrypt message with (n, e)
   1. To prevent overflows, we will operate bytewise while modulating by n (see rsa.c)
5. Decrypt resulting ciphertext with (n, d)

### When You're Done ###
Submit your code and pseudocode!!!