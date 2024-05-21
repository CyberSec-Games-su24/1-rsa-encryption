# RSA Encryption and Decryption #
This week, we will be focused on gaining a functional understanding of the Rivest-Shamir-Adleman (RSA) Encryption 
Algorithm. A public key block cipher. That's a lot of words at once, so lets break down what each of the relevant portions of 
this encryption suite ential.

## Table of Contents ##
- [RSA Encryption and Decryption](#rsa-encryption-and-decryption)
  - [Table of Contents](#table-of-contents)
  - [Glossary](#glossary)
- [What The Heck Is This Thing?](#what-the-heck-is-this-thing)
  - [Public Key Encryption](#public-key-encryption)
  - [Block Ciphers](#block-ciphers)
  - [How Is RSA Secure?](#how-is-rsa-secure)
- [The RSA Algorithm, In Nerd Language](#the-rsa-algorithm-in-nerd-language)
  - [Step By Step](#step-by-step)
    - [1. Defining two primes:](#1-defining-two-primes)
    - [2. Calculating the coprime n:](#2-calculating-the-coprime-n)
    - [3. Calculating the totient $\\phi$(n)](#3-calculating-the-totient-phin)
    - [4. Calculating the public key's exponent e](#4-calculating-the-public-keys-exponent-e)
    - [5. Calculating the private key's exponent d](#5-calculating-the-private-keys-exponent-d)
- [Sending A Message With RSA](#sending-a-message-with-rsa)
  - [Our message](#our-message)
  - [Encryption](#encryption)
  - [Decryption](#decryption)
  - [In Essence](#in-essence)

## Glossary ##
<dl>
<dt><strong>Encryption</strong></dt>
<dd>The cryptographic transformation of data to produce ciphertext. (NIST)</dd>
<dt><strong>Cipher</strong></dt>
<dd>Series of transformations that converts plaintext to ciphertext using the Cipher Key. (NIST)</dd>
<dt><strong>Plaintext</strong></dt>
<dd>Unencrypted information that may be input to an encryption operation. (NIST)</dd>
<dt><strong>Ciphertext</strong></dt>
<dd>Data in its encrypted form. (NIST)</dd>
<dt><strong>Key</strong></dt>
<dd>A parameter used in conjunction with a cryptographic algorithm that determines its operation. Examples applicable to this Standard include: 1. The computation of a digital signature from data, and 2. The verification of a digital signature. (NIST)</dd>
</dl>

# What The Heck Is This Thing? #

## Public Key Encryption ##
Public Key encryption is a type of asymmetric encryption. This means that the encrypting a message uses a different 
set of parameters than decrypting it. This asymmetric process requires a pair of keys; a public key and a mathematically 
derived private key. When the message is encrypted with a public key, the message can be decrypted with a private key derived 
from the encrypting key. We will learn more about symmetric encryptions later, but the basic is that a symmetric algorithm uses 
the same process to encrypt _and_ decrypt a message.

## Block Ciphers ##
A block cipher simply means the data we are processing to produce our ciphertext comes in blocks of a fixed size. In this exploration 
we are going to be working in RSA-2048, meaning that our message, no matter its length, will be split into 2048-bit chunks to be processed sequentially. 
If our plaintext is less than 2048 bits, the message will be padded with zeros until it is the desired length. If we pass RSA-2048 a 2049-bit 
plaintext, it will run the operation twice, once with the first 2048 bits and again with 1 bit padded with 2047 zeros, before concatinating the two results.

## How Is RSA Secure? ##
The security of RSA relies on the incomputablility of the factors of large numbers. As you'll see below, RSA uses two prime numbers as the multiplicative 
foundation for creating ciphertext. While these multiplicative steps are trivial to compute in one direction, calculating and verifying the correct factors of this large value is unfeasible with classical computers. This one directional computability is the basis for P versus NP, so enjoy that rabbit hole!

# The RSA Algorithm, In Nerd Language #
Because RSA is asymmetric, it can rely on the security of the keys and therefore its algorithm is computationally straight-forward. Most simply, RSA utilizes the selection of two prime numbers to manipulate in tandem with the plaintext to produce a ciphertext.

## Step By Step ##
### 1. Defining two primes: ###
We first select any two prime numbers p and q. In this example,<br>
p = 17<br>
q = 13

### 2. Calculating the coprime n: ###
A coprime number is simply a multiple of two primes.<br>
n = p x q = 221

### 3. Calculating the totient $\phi$(n) ###
Given n, $\phi$(n) = (p -1) x (q - 1)<br>
$\phi$(221) = (17 - 1) x (13 - 1) = 192

### 4. Calculating the public key's exponent e ###
To determine what the public key's exponent is, we need to find a number such that<br>
1 < e < $\phi$(n) and gcd(e, $\phi$(n)) = 1.<br>
In this case, 35 will work.<br>

### 5. Calculating the private key's exponent d ###
To calculate the private key's exponent, we need to find an integer d such that<br>
e\*d = 1 (mod $\phi$(n))<br>
In other words, (e*d) / $\phi$(n) has a remainder of 1.

To calculate d, the extended Euclidean algorithm is used. This will be covered further in the lab.

In this case, the 385 works with factors 35 and 11.
   

# Sending A Message With RSA #
Now that we have our coprime n and our exponents e and d, we can now successfully encrypt and decrypt messages in RSA.

## Our message ##
If we want to send a message, we must first convert it into an integer. To do so, we can convert each character of the message into a base 2^n value (binary, octal, or hex) using each character's ASCII value and concatinate the values to convert into an integer. In this case, I'm going to use hexadecimal because it is what I prefer, but there is really no significant difference between choosing any base.

Message: Hello,_World!

Hex Conversion: 48 65 6C 6C 6F 2C 20 57 6F 72 6C 64 21

Hex to decimal: 0x48656C6C6F2C20576F726C6421 = 5735816763073854918203775149089

## Encryption ##
To encrypt our message (m) with the public key (221, 35), we can use the equation m^e (mod n)

5735816763073854918203775149089^35 (mod 221). You might notice that the number we are doing a modulus operation on is enormous. To get around the computational limits, we use some tricks in the lab implementation, but the encryption returns c="�//s,_6sr/�L" when encoded to ascii.

Note: there are some quirks/imperfections in this implementation. This is a great opportunity to dig into what is causing this and see if you can make it more secure. If you're a tactile learner, this process can be a great way to expand your programming skills!

## Decryption ##
To decrypt a message, we can use whatever key the encryption didn't use, so in this case it'll be the private key. Similar to how the message was encrypted, the private key (221, 11) can be used with the equation c^11 to return m="Hello,_World!". This data output (along with what you find online) because the algorithm finctions byte-wise under the hood. Please see the code implementation for a better understanding if you'd like.

## In Essence ##
Put very simply, RSA relies on two keys. If you encrypt with one key, you can use the other key to decrypt. This occurs because the public key is used to generate the private key, producing multiplicative inverses that will reverse the manipulation caused by the other key.
