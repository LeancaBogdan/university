#pragma once
#include <string>
#include <vector>
	
	/// <summary>
	/// Trims leading and trailing spaces from a string.
	/// </summary>
	/// <param s>std::string to be trimmed.</param>
	/// </returns> std::string, with no leading and trailing spaces.
std::string trim(const std::string& s);

	/// <summary>
	/// Tokenizes a string.
	/// </summary>
	///	<param str>The std::string to be tokenized.</param>
	/// <param delimiter>Char, the delimiter used for tokenization.</param>
	/// <returns>std::vector of std::strings, containing the tokens</returns>
std::vector<std::string> tokenize(const std::string& str, char delimiter);
