--CyberSec Games 2024 
--Rhiannon Kilduff 

local numbers = {}
local prime_num
local p
local e
local q
local n 
local phi_n
local d 
local message = ""
local encoded_message = ""
local result
local ciphertext = ""
--local output_cipher



--check if number is prime 
function numbers.is_prime(num)

    for i = 2, math.floor((num / 2)+1) do
        --Ra
        if num % i == 0 then 
            return false --num  is not prime 
        end
    end

    return true

end
-- returns bool true or false 

--give me a random prime 
function numbers.generate_prime(min_num, max_num)

    prime_num = math.random(min_num, max_num)

    while not numbers.is_prime(prime_num) do
        prime_num = math.random(min_num, max_num)

    end

    return prime_num
    --when the number is prime return it
end

function numbers.invers_mod(e, phi)
    for d = 3, phi do
        if (d * e) % phi == 1 then
            return d
        end 
    end
end
-- returns  private key d  

function numbers.gcd(x, y)
    if y == 0 then
        return x 
    else
        return numbers.gcd(y, x%y)
    end
end
--manually duplicated the gcd() python method 

function numbers.ord(ch)
    return string.byte(ch)
end

--manually duplicated the ord() python method 




p = numbers.generate_prime(1000, 8000)
q = numbers.generate_prime(1000, 8000)

while p == q do
    q = numbers.generate_prime(1000, 8000)
end

n = p * q
phi_n = (p-1) * (q-1)
--finds phi of n 

e = math.random(3, phi_n -1)

while numbers.gcd(e, phi_n) ~= 1 do
    e = math.random(3, phi_n -1)
end
    -- checking for co primes 

d = numbers.invers_mod(e, phi_n)

print("Public Key: ", e)
print("Private Key: ", d)
print("n: ", n)
print("Phi of n ", phi_n)
print("p: ", p)
print("q" , q)
--this is how you print in Lua correct or I can't read documentation 

message = "Hello There"

for ch = 1, #message do 
    encoded_message = encoded_message(numbers.ord(string.sub(message, ch, ch)))
end

for _, ch in ipairs(encoded_message) do
    result = (ch^e) % n
    ciphertext = ciphertext .. tostring(result) .. ", "
end

-- Remove the trailing comma and space
ciphertext = ciphertext:sub(1, -3)
--this is me trying to figure out how to .join via internet crawling 
print(ciphertext)

-- output_cipher = io.open("secret.txt", "w")
-- output_cipher:write(ciphertext)
-- output_cipher:close()

-- for ch = 1, #ciphertext do
--     encoded_message = encoded_message(numbers.ord(string.sub(ciphertext, ch, ch)))
-- end


