# rsa-encryption

Rhiannon Kilduff 
Language: Lua
Complete: No
Project Type : CyberSec-su24


# Pseudocode

```lua\
function is_prime(num:int) --> bool 
		if num < 2 
			return false 
			-- integers less than 2 can never be prime 
		for i in range(2, num / 2 + 1) 
		-- range from 2, smallest possible num to num divided by 2 + 1 
		-- (num / 2+1) any factor of num must be <= to its sqr 
			--(this is me understanding the math Alex) 
			if mod i == 0 
			return False 
			-- num is not prime 
		return True 
		-- otherwise mod i will have remainder meaning it is prime 
function generate_prime(min_num:int, max_num:int)

	prime_num = random int (min_num and max_num) --> int
	-- generate a number withing the range 
	while is_prime(prime) is not prime 
		prime_num = random int (min_num and max_num) 
		-- while not a prime number try again unitl it is 
	return prime_num 
	--when number is prime return it 
	
function inverse_mod(e:int, phi:int) --> int 
	--e public part of key pair 
	--phi part of Euler’s totient function
		for d in range between 3 and phi 
			if (d * e) mod phi is equal to 1 
			-- if d x e mode phi is 1 return d 
			-- (again the math)
		return d
generate_ prime(min, max)  number for p 
generate_prime( min, max) number for q 

--check that p & q are not == 
while p == q 
	generate again

n = p * q 
phi(n) = (p-1) * (q-1)
-- finds phi of n 

e = random int between 3, phi(n) -1 
		-- int must be larger than 2 and less than phi(n)
	while the gcd of e and phi(n) - 1 =! 1
		e = random int between 3, phi(n) -1
		-- as long as e and phi_n are not co-prime pick a new e 
		
d = inverse_mod(e, phi) 
--private part of key pair 

message = "My Message" 
-- I probablty need to do this from a file but I'll worry about that later 
-- or maybe I'll just have a stupid block of strings 

encoded_message = for character in message convert to number representation
-- encode != encrypted 

ciphertext = character^e mod n for each character in encoded_message
-- message^public key(e) mod n 

ciphertext = output file 
	
--decryption 

encoded_message = character^d mod n for each character in ciphertext
-- message^private key(d) mod n 

decryp_ message = for character in message convert to ascii representation 

decryp_ message = output file 

```
* This pseudocode was 100% ripped from an indepth rsa in python youtube video
* I didn't feel like learning to read your C 
* I will also take no shit for spelling errors :) 

