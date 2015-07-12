#pragma once
std::vector<std::string> split(const std::string& input, char delimiter){
	std::istringstream stream(input);

	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

