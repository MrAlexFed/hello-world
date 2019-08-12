#include "Header.h"

/*Перегрузка оператора * со строкой и целым числом.*/
std::string operator*(const std::string str, const int num)
{
	std::string result = "";
	for (int i = 0; i < num; i++)
	{
		result += str;
	}
	return result;
}
/*Добавляет символы # в конец строки для того, чтобы строка содержала
в себе в двоичном представлении целое колличество блоков разбиения*/
std::string Binary_blocks::string_to_right_lenght(std::string input)
{
	int rest;
	rest = (input.length() * size_of_char) % size_of_block;
	if(rest != 0)
		input += static_cast<std::string>("#")
		* ((size_of_block - rest)/size_of_char);
	return input;
}

/*Нарезает строку на блоки*/
std::vector<std::string> Binary_blocks::cust_string_to_blocks(const std::string input)
{
	std::vector<std::string> blocks;
	int length_of_block = size_of_block / size_of_char;
	int quantity_of_blocks = input.length() / length_of_block;
	for (int i = 0; i < quantity_of_blocks; i++)
	{
		std::string push = input.substr(i * length_of_block, length_of_block);
		blocks.push_back(push);
	}
	return blocks;
}

/*Превращает обычную строку в бинарную*/
std::string Binary_blocks::string_to_binary_format(const std::string input)
{
	std::string result = "";
	std::bitset<size_of_char> binary;
	for (char entry : input)
	{
		binary = entry;
		result += binary.to_string();
	}
	return result;
}
/*Переводит начальную строку в вектор бинарных блоков*/
std::vector<std::string> Binary_blocks::string_preparation(std::string input)
{
	input = string_to_right_lenght(input);
	std::vector<std::string> vec;
	std::vector<std::string> result;
	vec = cust_string_to_blocks(input);
	std::string binary_str;
	for (std::string str : vec)
	{
		binary_str = string_to_binary_format(str);
		result.push_back(binary_str);
	}
	return result;
}

/*Производит операцию XOR над бинарными строками*/
std::string XOR(const std::string s1, const std::string s2)
{
	std::string result = "";
	for (int i = 0; i < s1.length(); i++)
	{
		bool a = static_cast<int>(s1[i]) - 48;
		bool b = static_cast<int>(s2[i]) - 48;
		if (a ^ b)
			result += "1";
		else
			result += "0";
	}
	return result;
}

/*Производит первоначальную перестановку элементов блока*/
std::string Coded_string::transposition1(const std::string input)
{
	int s[] = { 57, 49, 41, 33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21,
	13, 5, 63, 55, 47, 39, 31, 23, 15, 7, 56, 48, 40,
	32, 24, 16, 8, 0, 58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30,
	22, 14, 6 };
	char result[65];
	result[64] = '\0';
	for (int i = 0; i < 64; i++)
	{
		result[i] = input[s[i]];
	}
	std::string output = static_cast<std::string>(result);
	return output;
}

/*Разбивает ключ на две части с одновременной перестановкой элементов*/
void Encription::key_to_halve(std::string key, char a[], char b[])
{
	a[28] = '\0';
	b[28] = '\0';
	a[0] = key[49];
	a[1] = key[42];
	a[2] = key[35];
	a[3] = key[28];
	a[4] = key[21];
	a[5] = key[14];
	a[6] = key[7];
	a[7] = key[0];
	a[8] = key[50];
	a[9] = key[43];
	a[10] = key[36];
	a[11] = key[29];
	a[12] = key[22];
	a[13] = key[15];
	a[14] = key[8];
	a[15] = key[1];
	a[16] = key[51];
	a[17] = key[44];
	a[18] = key[37];
	a[19] = key[30];
	a[20] = key[23];
	a[21] = key[16];
	a[22] = key[9];
	a[23] = key[2];
	a[24] = key[52];
	a[25] = key[47];
	a[26] = key[38];
	a[27] = key[31];

	b[0] = key[55];
	b[1] = key[48];
	b[2] = key[41];
	b[3] = key[34];
	b[4] = key[27];
	b[5] = key[20];
	b[6] = key[13];
	b[7] = key[6];
	b[8] = key[54];
	b[9] = key[47];
	b[10] = key[40];
	b[11] = key[33];
	b[12] = key[26];
	b[13] = key[19];
	b[14] = key[12];
	b[15] = key[5];
	b[16] = key[53];
	b[17] = key[46];
	b[18] = key[39];
	b[19] = key[32];
	b[20] = key[25];
	b[21] = key[18];
	b[22] = key[11];
	b[23] = key[4];
	b[24] = key[24];
	b[25] = key[17];
	b[26] = key[10];
	b[27] = key[3];
}
/*Производит 16 ключей из двух перемешанных груп первоначального ключа */
std::vector<std::string> Encription::cyclic_shift_key(const char a[], const char b[])
{
	std::vector<std::string> keys;
	std::string key;
	std::string first = static_cast<std::string>(a);
	std::string second = static_cast<std::string>(b);
	for (int i = 1; i <= 16; i++)
	{
		if (i == 1 || i == 2 || i == 9 || i == 16)
		{
			first = first.substr(1, first.length()-1) + first.substr(0, 1);
			second = second.substr(1, second.length()-1) + second.substr(0, 1);
		}
		else
		{
			first = first.substr(2, first.length()-2) + first.substr(0, 2);
			second = second.substr(2, second.length()-2) + second.substr(0, 2);
		}
		std::string comb = first + second;
		char c[49];
		c[48] = '\0';
		c[0] = comb[13];
		c[1] = comb[16];
		c[2] = comb[10];
		c[3] = comb[23];
		c[4] = comb[0];
		c[5] = comb[4];
		c[6] = comb[2];
		c[7] = comb[27];
		c[8] = comb[14];
		c[9] = comb[5];
		c[10] = comb[20];
		c[11] = comb[9];
		c[12] = comb[22];
		c[13] = comb[18];
		c[14] = comb[11];
		c[15] = comb[3];
		c[16] = comb[25];
		c[17] = comb[7];
		c[18] = comb[15];
		c[19] = comb[6];
		c[20] = comb[26];
		c[21] = comb[19];
		c[22] = comb[12];
		c[23] = comb[1];
		c[24] = comb[40];
		c[25] = comb[51];
		c[26] = comb[30];
		c[27] = comb[36];
		c[28] = comb[46];
		c[29] = comb[54];
		c[30] = comb[29];
		c[31] = comb[39];
		c[32] = comb[50];
		c[33] = comb[44];
		c[34] = comb[32];
		c[35] = comb[47];
		c[36] = comb[43];
		c[37] = comb[48];
		c[38] = comb[38];
		c[39] = comb[55];
		c[40] = comb[33];
		c[41] = comb[52];
		c[42] = comb[45];
		c[43] = comb[41];
		c[44] = comb[49];
		c[45] = comb[35];
		c[46] = comb[28];
		c[47] = comb[31];

		key = static_cast<std::string>(c);
		keys.push_back(key);
	}
	return keys;
}
/*Производит деления ключа на 16 частей для каждого раунда функции f()*/
std::vector<std::string> Encription::key_separation(const std::string key)
{
	char a[29];
	char b[29];
	std::vector<std::string> keys;
	key_to_halve(key, a, b);
	keys = cyclic_shift_key(a, b);
	return keys;
}
/*Производит расширение и перемешивание ключа Ka*/
std::string Encription::key_extension(const std::string key)
{
	int s1[] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12,
	5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11,
	9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7,
	3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14,
	10, 0, 6, 13};
	
	char a[49];
	a[48] = '\0';
	for (int i = 0; i < 48; i++)
	{
		a[i] = key[s1[i]];
	}
	std::string result = static_cast<std::string>(a);
	return result;
}

/*Производит перемешивание и расширение бинарной строки длины 32 
в ходе процесса выполнении функции f()*/
std::string Encription::transposition2(const std::string b)
{
	char trans[49];
	trans[48] = '\0';
	trans[0] = b[31];
	trans[46] = b[31];
	trans[1] = b[0];
	trans[47] = b[0];
	for (int i = 0; i < 7; i++)
	{
		trans[i * 6 + 2] = b[i * 4 + 1];
		trans[i * 6 + 3] = b[i * 4 + 2];
		trans[i * 6 + 4] = b[i * 4 + 3];
		trans[i * 6 + 5] = b[i * 4 + 4];
		trans[i * 6 + 6] = b[i * 4 + 3];
		trans[i * 6 + 7] = b[i * 4 + 4];
	}
	trans[44] = b[29];
	trans[45] = b[30];
	return static_cast<std::string>(trans);
}
/*Разбивает бинарную строку на 8 и после специальных преобразований 
соединяет её снова*/
std::string Encription::splitting_and_combination(const std::string input)
{
	std::string result = "";
	std::vector<std::string> s;
	for (int i = 0; i < 8; i++)
	{
		s.push_back(input.substr(i * 6, 6));
	}

	int seq[8][4][16] = { 
		{ { 13, 14, 0, 3, 10, 4, 7, 9, 11, 8, 12, 6, 1,
		15, 2, 5 },{ 8, 2, 11, 13, 4, 1, 14, 7, 5, 15, 0, 3, 10, 6, 9,
		12 },{ 14, 9, 3, 10, 0, 7, 13, 4, 8, 5, 6, 15, 11, 12, 1, 2 },
		{ 1, 4, 14, 7, 11, 13, 8, 2, 6, 3, 5, 10, 12, 0, 15, 9 } },

		{ { 15, 8, 3, 14, 4, 2, 9, 5, 0, 11, 10, 1, 13,
		7, 6, 12 },{ 6, 15, 9, 5, 3, 12, 10, 0, 13, 8, 4, 11, 14,
		2, 1, 7 },{ 9, 14, 5, 8, 2, 4, 15, 3, 10, 7, 6, 13, 1, 11, 12,
		0 },{ 10, 5, 3, 15, 12, 9, 0, 6, 1, 2, 8, 4, 11, 14, 7, 13 } },
		
		{{13, 3, 11, 5, 14, 8, 0, 6, 4, 15, 1, 12, 7, 2, 10, 9},
		{4, 13, 1, 8, 7, 2, 14, 11, 15, 10, 12, 3, 9, 5, 0, 6},
		{6, 5, 8, 11, 13, 14, 3, 0, 9, 2, 4, 1, 10, 7, 15, 12},
		{1, 11, 7, 2, 8, 13, 4, 14, 6, 12, 10, 15, 3, 0, 9, 5}},

		{{9, 0, 7, 11, 12, 5, 10, 6, 15, 3, 1, 14, 2, 8, 4, 13},
		{5, 10, 12, 6, 0, 15, 3, 9, 8, 13, 11, 1, 7, 2, 14, 4},
		{10, 7, 9, 12, 5, 0, 6, 11, 3, 14, 4, 2, 8, 13, 15, 1},
		{3, 9, 15, 0, 6, 10, 5, 12, 14, 2, 1, 7, 13, 4, 8, 11}},

		{{5, 15, 9, 10, 0, 3, 14, 4, 2, 12, 7, 1, 13, 6, 8, 11},
		{6, 9, 3, 15, 5, 12, 0, 10, 8, 7, 13, 4, 2, 11, 14, 1},
		{15, 0, 10, 9, 3, 5, 4, 14, 8, 11, 1, 7, 6, 12, 13, 2},
		{12, 5, 0, 6, 15, 10, 9, 3, 7, 2, 14, 11, 8, 1, 4, 13}},

		{{4, 3, 7, 10, 9, 0, 14, 13, 15, 5, 12, 6, 2, 11, 1, 8},
		{14, 13, 11, 4, 2, 7, 1, 8, 9, 10, 5, 3, 15, 0, 12, 6},
		{13, 0, 10, 9, 4, 3, 7, 14, 1, 15, 6, 12, 8, 5, 11, 2},
		{1, 7, 4, 14, 11, 8, 13, 2, 10, 12, 3, 5, 6, 15, 0, 9}},

		{{4, 10, 15, 12, 2, 9, 1, 6, 11, 5, 0, 3, 7, 14, 13, 8},
		{10, 15, 6, 0, 5, 3, 12, 9, 1, 8, 11, 13, 14, 4, 7, 2},
		{2, 12, 9, 6, 15, 10, 4, 1, 5, 11, 3, 0, 8, 7, 14, 13},
		{12, 6, 3, 9, 0, 5, 10, 15, 2, 13, 4, 14, 7, 11, 1, 8}},

		{{13, 10, 7, 3, 9, 14, 4, 2, 15, 12, 1, 5, 6, 11, 8},
		{2, 7, 13, 1, 4, 14, 11, 8, 15, 12, 6, 10, 9, 5, 0, 3},
		{4, 13, 14, 0, 9, 3, 7, 10, 1, 8, 2, 11, 15, 5, 12, 6},
		{8, 11, 7, 14, 2, 4, 13, 1, 6, 5, 9, 0, 12, 15, 3, 10}}
	};
	
	std::bitset<4> binary;
	std::string row;
	std::string col;
	int row_i = 0;
	int col_i = 0;
	for (int i = 0; i < 8; i++)
	{
		row = s[i].substr(0, 1) + s[i].substr(s[i].length() - 1, 1);
		col = s[i].substr(1, s[i].length() - 2);
		row_i = 0;
		col_i = 0;
		for(int j=0; j < 2; j++)
		{
			row_i += static_cast<int>(row[j] - '0') * pow(2, 1-j);
		}
		for (int j = 0; j < 4; j++)
		{
			col_i += static_cast<int>(col[j] - '0') * pow(2, 3-j);
		}
		binary = seq[i][row_i][col_i];
		result += binary.to_string();
	}
	return result;
}
/*Производит перестановку номер 3*/
std::string Encription::transposition3(const std::string input)
{
	int s[] = { 28, 24, 20, 16, 12, 8, 4, 0, 29, 25, 21, 17, 13, 9,
	5, 1, 30, 26, 22, 18, 14, 10, 6, 2, 31, 27, 23, 19, 15, 11, 7, 3 };
	char a[33];
	a[32] = '\0';
	for (int i = 0; i < 32; i++)
	{
		a[i] = input[s[i]];
	}
	std::string result = static_cast<std::string>(a);
	return result;
}
/*Функция f()*/
std::string Encription::f(const std::string key_i, const std::string key_a, const std::string key_b, const std::string b)
{
	std::string result = transposition2(b);
	result = XOR(key_i, result);
	result = XOR(key_extension(key_a), result);
	result = XOR(splitting_and_combination(result), key_b);
	result = transposition3(result);
	return result;
}
/*Перестановка четвёртая*/
std::string Coded_string::transposition4(const std::string input)
{
	int s[] = { 39, 7, 47, 15, 55, 23, 63, 31, 38, 6,
	46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61,
	29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11,
	51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33,
	1, 41, 9, 49, 17, 57, 25, 32, 0, 40, 8, 48, 16, 56, 24 };

	char a[65];
	a[64] = '\0';
	for (int i = 0; i < 64; i++)
	{
		a[i] = input[s[i]];
	}
	std::string result = static_cast<std::string>(a);
	return result;
}
/*Шифрование бинарного блока*/
std::string Coded_string::encryption(std::string input, std::string key)
{
	std::string result;
	result = transposition1(input);
	std::string a, b;
	a = result.substr(0, 32);
	b = result.substr(32, 32);
	std::string t;
	std::string key_a = key.substr(0, 16);
	std::string key_b = key.substr(16, 32);
	std::string key_d = key.substr(48, 56);
	std::vector<std::string> key_i = key_separation(key_d);
	for (int i = 0; i < 16; i++)
	{
		t = a;
		a = b;
		b = XOR(t, f(key_i[i], key_a, key_b, b));
	}
	result = a + b;
	//std::cout << result << "\n";
	result = transposition4(result);
	return result;
}
/*Проверка числа на простоту*/
bool Coded_string::is_prime(long n) {
	bool result = true; 
	double r = n, root = sqrt(r);
	for (int trial_factor = 2;
		result && trial_factor <= root; trial_factor++)
		result = (n % trial_factor != 0);
	return result;
}
/*Генератор ключа*/
std::string Coded_string::key_generator()
{
	/*srand(static_cast<unsigned>(time(0)));*/
	srand(11);
	std::string key;
	int a;
	long num;
	while (true)
	{
		num = 0;
		key = "";
		for (int i = 0; i < 104; i++)
		{
			a = rand() % 2;
			key += std::to_string(a);
			num += pow(a, 104 - i - 1);
		}
		if (is_prime(num))
			break;
	}
	return key;
}
/*Превращение бинарной строки в символьную*/
std::string Encription::binary_into_literal(const std::string input)
{
	std::vector<int> num(input.length());
	char a;
	for(int i = 0; i < input.length(); i++)
	{
		num[i] = input[i] - '0';
	}
	int size1 = input.length() / size_of_char;
	int number;
	std::vector<int> numbers(size1);
	for (int i = 0; i < size1; i++)
	{
		number = 0;
		for (int j = 0; j < size_of_char; j++)
		{
			number += num[i*size_of_char + j] * pow(2, size_of_char - j-1);
		}
		numbers[i] = number;
	}
	std::string result="";
	for (int i = 0; i < size1; i++)
	{
		result += static_cast<char>(numbers[i]);
	}
	return result;
}
/*Шифрование символьной строки в символьную строку */
std::string Coded_string::total_encryption(std::vector<std::string> vec)
{
	std::string result = "";
	for (std::string entry : vec)
	{
		result += encryption(entry, key);
	}
	result = binary_into_literal(result);
	return result;
}
/*Обратная перестановка четыре*/
std::string Uncoded_string::untransposition4(const std::string input)
{
	int s[] = { 39, 7, 47, 15, 55, 23, 63, 31, 38, 6,
		46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61,
		29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11,
		51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33,
		1, 41, 9, 49, 17, 57, 25, 32, 0, 40, 8, 48, 16, 56, 24 };

	char a[65];
	a[64] = '\0';
	for (int i = 0; i < 64; i++)
	{
		a[s[i]] = input[i];
	}
	std::string result = static_cast<std::string>(a);
	return result;
}
std::string Uncoded_string::key_extension(const std::string key)
{
	int s1[] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12,
		5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11,
		9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7,
		3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14,
		10, 0, 6, 13 };

	char a[49];
	a[48] = '\0';
	for (int i = 0; i < 48; i++)
	{
		a[i] = key[s1[i]];
	}
	std::string result = static_cast<std::string>(a);
	return result;
}

std::string Uncoded_string::untransposition1(const std::string input)
{
	int s[] = { 57, 49, 41, 33, 25, 17, 9, 1, 59, 51,
		43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21,
		13, 5, 63, 55, 47, 39, 31, 23, 15, 7, 56, 48, 40,
		32, 24, 16, 8, 0, 58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30,
		22, 14, 6 };
	char result[65];
	result[64] = '\0';
	for (int i = 0; i < 64; i++)
	{
		result[s[i]] = input[i];
	}
	std::string output = static_cast<std::string>(result);
	return output;
}

std::string Uncoded_string::unencryption(std::string input, std::string key)
{
	std::string result;
	result = untransposition4(input);
	std::string a, b;
	a = result.substr(0, 32);
	b = result.substr(32, 32);
	std::string t;
	std::string key_a = key.substr(0, 16);
	std::string key_b = key.substr(16, 32);
	std::string key_d = key.substr(48, 56);
	std::vector<std::string> key_i = key_separation(key_d);
	for (int i = 0; i < 16; i++)
	{
		t = b;
		b = a;
		a = XOR(t, f(key_i[15 - i], key_a, key_b, b));
	}
	result = a + b;
	result = untransposition1(result);
	return result;
}
std::string Uncoded_string::total_unencryption(std::vector<std::string> vec)
{
	std::string result = "";
	for (std::string entry : vec)
	{
		result += unencryption(entry, key);
	}
	result = binary_into_literal(result);
	return result;
}
