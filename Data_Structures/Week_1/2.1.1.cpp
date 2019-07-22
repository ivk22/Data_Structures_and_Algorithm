#include <iostream>
#include <stack>
#include <string>

struct Bracket {
	Bracket(char brc, int pos) {
		type=brc;
		position = pos;
	}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;

};

int main() {
	std::string text;
	getline(std::cin, text);
	bool flag = 1;

	std::stack <Bracket> opening_brackets_stack;
	for (int position = 0; position < text.size(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			opening_brackets_stack.push({ next , position +1});

		}

		if (next == ')' || next == ']' || next == '}') {
			if (opening_brackets_stack.empty()) {
				std::cout << position + 1;
				flag = 0;
				break;
			}
			if (opening_brackets_stack.top().Matchc(next)) {
				opening_brackets_stack.pop();
			}
			else {
				std::cout << position+1;
				flag = 0;
				break;
			}
		}
	}
	if (flag) {
		if (opening_brackets_stack.empty()) {
			std::cout << "Success";
		}
		else {
			Bracket b = { '1',1 };
			while (!opening_brackets_stack.empty()) {
				b = opening_brackets_stack.top();
				opening_brackets_stack.pop();
			}
			std::cout << b.position;
		}
	}

	return 0;
}
