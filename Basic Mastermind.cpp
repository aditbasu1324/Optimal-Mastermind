#include <iostream>
#include <vector>
#include <array>
using namespace std;

// on hold
vector<int> getUserInput(int color, int places)
{
	cout << "Enter a code with a space after each number: ";
	vector<int> code{};
	int x;
	while (cin >> x)
	{
		if (0 <= x && x<color)
		{
			code.push_back(x);
		}
	}
	if (code.size() != places) cout << "Error";
	return code;
}

// power function for N
int power(int base, int exp)
{
	int result{ 1 };
	while (exp > 0)
	{
		if (exp % 2 == 1)
			result *= base;
		base = base * base;
		exp = exp / 2;
	}
	return result;
}

// encoding red and white pins
// this is O(color,places)
int score(const vector<int>& a, const vector<int>& b, int places, int color)
{
	vector<int> a_count((size_t)color);
	vector<int> b_count((size_t)color);
	for (const auto ele : a)
	{
		a_count[(size_t)ele] += 1;
	}
	for (const auto ele : b)
	{
		b_count[(size_t)ele] += 1;
	}
	int white_count{ 0 };
	int red_count{ 0 };
	for (int i{ 0 }; i < color; ++i)
	{
		white_count += min(a_count[(size_t)i], b_count[(size_t)i]);
	}
	for (int i{ 0 }; i < places; ++i)
	{
		red_count += (a[(size_t)i] == b[(size_t)i]);
	}
	// all red pins are also white pins
	return red_count * places + (white_count - red_count);
}

// decoding the code into a number
int decode(vector<int> a, int color, int places)
{
	int result{ 0 };
	int base{ 1 };
	for (int i{ places - 1 }; i>=0; --i)
	{
		result += a[(size_t)i] * base;
		base *= color;
	}
	return result;
}

int ComputerOutput(const vector<int>& candidate_codes, const vector<vector<int>>& storage, int N, int places, int count)
{	
	// additional code needed since computer output process doesn't appropriately distinguish values when one code is left.
	if (count == 1)
	{
		for (int i{ 0 }; i < N; ++i)
		{
			if (candidate_codes[(size_t)i] == 0)
			{
				return i;
			}
		}
	}

	// make decision based on candidate codes
	int current_maximum{ N + 1 };
	int max_index{ 0 };
	for (int i{ 0 }; i < N; ++i)
	{
		// keep track of number of each score
		vector<int> possible_scores((size_t)(places * places+1));
		for (int j{ 0 }; j < N; ++j)
		{
			if (candidate_codes[(size_t)j] == 0)
				possible_scores[(size_t)storage[(size_t)i][(size_t)j]] += 1;
		}
		int maximum{ 0 };
		for (const auto ele : possible_scores)
		{
			if (ele > maximum) maximum = ele;
		}
		if (maximum < current_maximum)
		{
			current_maximum = maximum;
			max_index = i;
		}
	}
	return max_index;
}

void mastermind(int color, int places, vector<int> solution)
{
	cout << "In this game, there are " << color << " colors " << "and " << places << " places" << '\n';
	// solution is the final code that needs to be guessed
	int no_of_guesses{ 10 };
	int numeric_solution{ decode(solution, color, places) };
	int N{ power(color,places) };
	vector<vector<int>> storage((size_t)N, vector<int> ((size_t)N));
	vector<vector<int>> all_codes;

	// code to generate all_codes
	vector<int> v((size_t)places);
	int index{ places - 1 };
	for (int i{ 0 }; i < N-1; ++i)
	{
		int current_index{ index };
		all_codes.push_back(v);
		while (v[(size_t)current_index] == color - 1)
		{
			v[(size_t)current_index] = 0;
			current_index = current_index - 1;
		}
		v[(size_t)current_index] += 1;
	}

	all_codes.push_back(v);
	// code for storage
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			storage[(size_t)i][(size_t)j] = score(all_codes[(size_t)i], all_codes[(size_t)j], places, color);
		}
	}

	// scores in storage are red pins*places + white pins
	// can store red and overall separately for faster precomputation
	// in all codes process store changes to the vector position


	vector<int> candidate_codes((size_t)N,0); // zero means candidate
	int count{ N };
	while (no_of_guesses > 0)
	{
		cout << "The number of potential codes is: " << count << '\n';
		int computer_index{ ComputerOutput(candidate_codes, storage, N, places, count) };
		int value{ storage[(size_t)computer_index][(size_t)numeric_solution] };
		// For output presentation
		cout << "Code guessed ";
		for (const auto ele : all_codes[(size_t)computer_index])
		{
			cout << ele << " ";
		}
		// then find no of pins
		cout << '\n';
		int red_pins{ value / places };
		int white_pins{ value - red_pins * places };
		cout << red_pins << " Red Pins and " << white_pins << " White Pins." << "\n";
		
		// if all red done, if not then reduce candidate codes
		no_of_guesses--;
		if (value == places * places)
		{
			cout << "Code has been found.";
			break;
		}
		for (int i{ 0 }; i < N; ++i)
		{
			if (candidate_codes[(size_t)i]==0 && storage[(size_t)computer_index][(size_t)i] != value)
			{
				candidate_codes[(size_t)i] = 1;
				count -= 1;
			}
		}
		cout << '\n';
	}
	if (no_of_guesses == 0)
	{
		cout << "Code was not found.";
	}
}

int main()
{
	vector<int> v{1,2,1,3, 2};
	mastermind(4, 5, v);
	return 0;
}