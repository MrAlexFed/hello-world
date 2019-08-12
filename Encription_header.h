#ifndef HEADER_H_
#define HEADER_H_

#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <ctime>

 const int size_of_block = 64;
 const int q_of_rounds = 16;
 const int size_of_char = 8;

 std::string operator*(const std::string str, const int num);
 std::string XOR(const std::string s1, const std::string s2);

 class Binary_blocks
 {
 private:
	 std::vector<std::string> message;
	 std::string string_to_right_lenght(std::string input);
	 std::vector<std::string> cust_string_to_blocks(const std::string input);
	 std::string string_to_binary_format(const std::string input);
	 std::vector<std::string> string_preparation(std::string input);
 public:
	 Binary_blocks(std::string message_)
	 {
		 message = string_preparation(message_);
	 }
	 std::vector<std::string> get_message() const
	 {
		 return message;
	 }
 };

 class Encription
 {
 protected:
	 std::string key;
	 void key_to_halve(std::string key, char a[], char b[]);
	 std::vector<std::string> cyclic_shift_key(const char a[], const char b[]);
	 std::vector<std::string> key_separation(const std::string key);
	 std::string key_extension(const std::string key);
	 std::string transposition2(const std::string b);
	 std::string splitting_and_combination(const std::string input);
	 std::string transposition3(const std::string input);
	 std::string f(const std::string key_i, const std::string key_a, const std::string key_b, const std::string b);
	 std::string binary_into_literal(const std::string input);
 };


class Coded_string: public Encription
{
private:
	std::string coded_str;
	std::string key;

	std::string key_generator();
	bool is_prime(long n);
	std::string transposition1(const std::string input);
	std::string transposition4(const std::string input);
	std::string encryption(std::string input, std::string key);
	std::string total_encryption(std::vector<std::string> vec);
public:
	Coded_string(Binary_blocks& block)
	{
		key = key_generator();
		coded_str = total_encryption(block.get_message());
	}
	std::string get_key()
	{
		return key;
	}
	std::string get_string()
	{
		return coded_str;
	}
};

class Uncoded_string: public Encription
{
private:
	std::string uncoded_str;
	std::string key;

	std::string untransposition4(const std::string input);
	std::string key_extension(const std::string key);
	std::string untransposition1(const std::string input);
	std::string unencryption(std::string input, std::string key);
	std::string total_unencryption(std::vector<std::string> vec);
	
public:
	 Uncoded_string(Binary_blocks& block, Coded_string& code)
	{
		key = code.get_key();
		uncoded_str = total_unencryption(block.get_message());
	}
	std::string get_string()
	{
		std::string result = uncoded_str;
		for(int i = 0; i < result.length();)
		{
			if (result[i] == '#')
			{
				result = result.substr(0, i) + result.substr(i+1, result.length()-i-1);
			}
			else
			{
				i++;
			}
		}
		return result;
	}
};
#endif
