int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to determine if the operator is left associative
bool isLeftAssociative(char op) {
    // In standard arithmetic, all operators here are left associative
    return op == '+' || op == '-' || op == '*' || op == '/';
}

string inf2pos(const string& expr) {
  string output;
  stack<char> operators;
  map<char, int> prec;
  prec['+'] = 1; prec['-'] = 1;
  prec['*'] = 2; prec['/'] = 2;

  for (size_t i = 0; i < expr.length(); ++i) {
    char token = expr[i];

    if (isdigit(token)) {
      // Add the number to the output queue
      while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
          output += expr[i++];
      }
      output += ' '; // Add a space to separate numbers
      --i; // Adjust for the increment in the for loop
    } else if (token == '+' || token == '-' || token == '*' || token == '/') {
      while (!operators.empty() && operators.top() != '(' && (prec[operators.top()] > prec[token] || (prec[operators.top()] == prec[token] && isLeftAssociative(token)))) {
        output += operators.top();
        output += ' ';
        operators.pop();
      }
      operators.push(token);
    } else if (token == '(') {
      operators.push(token);
    } else if (token == ')') {
      while (!operators.empty() && operators.top() != '(') {
        output += operators.top();
        output += ' ';
        operators.pop();
    }
      operators.pop(); // Remove the '(' from the stack
    }
  }

  while (!operators.empty()) {
    output += operators.top();
    output += ' ';
    operators.pop();
  }

  return output;
}

int evaluate(const string& postfix) {
  stack<int> stack;
  istringstream tokens(postfix);
  string token;

  while (tokens >> token) {
    if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
      // If token is a number (handles negative numbers too)
      stack.push(stoi(token));  // Convert string to integer and push onto the stack
    } else {
      // Operator found, pop two elements from stack
      int val2 = stack.top();  // Second operand
      stack.pop();
      int val1 = stack.top();  // First operand
      stack.pop();

      switch (token[0]) {
        case '+':
          stack.push(val1 + val2);
          break;
        case '-':
          stack.push(val1 - val2);
          break;
        case '*':
          stack.push(val1 * val2);
          break;
        case '/':
          if (val2 != 0) {
              stack.push(val1 / val2);
          } else {
            cerr << "Error: Division by zero" << endl;
            return 0;  // Error handling for division by zero
          }
          break;
      }
    }
  }

  // The result is the last item in the stack
  return stack.top();
}

int32_t main() {
  string s = "2 + 6*3";
  string ss = inf2pos(s);
  cout << evaluate(ss);
}
