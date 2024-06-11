#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;
size_t currentIndex = 0;
size_t stop = 0;

// Token structure to hold token type and value
struct Token {
    string type;
    string value;
};

vector<Token> tokens;
vector<string> SymbolTable;

class Lexer {
public:
    // Function to tokenize the input C code
    vector<Token> tokenize(string code) {
        vector<Token> tokens;

        // Regular expression to match C-style comments
        regex comment_regex("(//.|/\\.?\\/)");

        // Remove all comments from the code
        code = regex_replace(code, comment_regex, "");
        // Regular expressions for various token types
        regex int_keyword("\\bint\\b");
        regex float_keyword("\\bfloat\\b");
        regex char_keyword("\\bchar\\b");
        regex void_keyword("\\bvoid\\b");
        regex double_keyword("\\bdouble\\b");
        regex long_keyword("\\blong\\b");
        regex short_keyword("\\bshort\\b");
        regex unsigned_keyword("\\bunsigned\\b");
        regex signed_keyword("\\bsigned\\b");
        regex bool_keyword("\\b_Bool\\b");
        regex complex_keyword("\\b_Complex\\b");
        regex imaginary_keyword("\\b_Imaginary\\b");
        regex balignas_keyword("\\balignas\\b");
        regex balignof_keyword("\\balignof\\b");
        regex asm_keyword("\\basm\\b");
        regex auto_keyword("\\bauto\\b");
        regex break_keyword("\\bbreak\\b");
        regex case_keyword("\\bcase\\b");
        regex const_keyword("\\bconst\\b");
        regex continue_keyword("\\bcontinue\\b");
        regex default_keyword("\\bdefault\\b");
        regex do_keyword("\\bdo\\b");
        regex else_keyword("\\belse\\b");
        regex enum_keyword("\\benum\\b");
        regex extern_keyword("\\bextern\\b");
        regex for_keyword("\\bfor\\b");
        regex goto_keyword("\\bgoto\\b");
        regex if_keyword("\\bif\\b");
        regex register_keyword("\\bregister\\b");
        regex return_keyword("\\breturn\\b");
        regex sizeof_keyword("\\bsizeof\\b");
        regex static_keyword("\\bstatic\\b");
        regex struct_keyword("\\bstruct\\b");
        regex switch_keyword("\\bswitch\\b");
        regex typedef_keyword("\\btypedef\\b");
        regex union_keyword("\\bunion\\b");
        regex volatile_keyword("\\bvolatile\\b");
        regex while_keyword("\\bwhile\\b");
        regex alignas_keyword("\\b_Alignas\\b");
        regex alignof_keyword("\\b_Alignof\\b");
        regex atomic_keyword("\\b_Atomic\\b");
        regex generic_keyword("\\b_Generic\\b");
        regex noreturn_keyword("\\b_Noreturn\\b");
        regex static_assert_keyword("\\b_Static_assert\\b");
        regex thread_local_keyword("\\b_Thread_local\\b");

        regex identifier("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b");
        regex floating_point_literal("\\b\\d+\\.\\d+\\b");
        regex integer_literal("\\b\\d+\\b");
        regex char_literal("'([^'\\\\]|\\\\.)*'");
        regex string_literal("\"([^\"\\\\]|\\\\.)*\"");
        regex plus_assignment("\\+=");
        regex minus_assignment("-=");
        regex multiply_assignment("\\*=");
        regex divide_assignment("/=");
        regex modulus_assignment("%=");
        regex bitwise_and_assignment("&=");
        regex bitwise_or_assignment("\\|=");
        regex bitwise_xor_assignment("\\^=");
        regex shift_left_assignment("<<=");
        regex shift_right_assignment(">>=");
        regex shift_left("<<");
        regex shift_right(">>");
        regex equal("==");
        regex not_equal("!=");
        regex less_than_or_equal("<=");
        regex greater_than_or_equal(">=");
        regex logical_and("\\&\\&");
        regex logical_or("\\|\\|");
        regex increment("\\+\\+");
        regex decrement("--");
        regex plus("\\+");
        regex minus("-");
        regex multiply("\\*");
        regex divide("/");
        regex modulus("%");
        regex bitwise_and("&");
        regex bitwise_or("\\|");
        regex bitwise_xor("\\^");
        regex logical_not("!");
        regex bitwise_not("~");
        regex less_than("<");
        regex greater_than(">");
        regex conditional("\\?");
        regex assignment("=");
        regex colon(":");
        regex comma(",");
        regex dot("\\.");
        regex open_paren("\\(");
        regex close_paren("\\)");
        regex open_brace("\\{");
        regex close_brace("\\}");
        regex open_square_bracket("\\[");
        regex close_square_bracket("\\]");
        regex hash("#");
        regex at("@");
        regex dollar("\\$");
        regex semicolon(";");

        vector<regex> regexes = {
        int_keyword,
        float_keyword,
        char_keyword,
        void_keyword,
        double_keyword,
        long_keyword,
        short_keyword,
        unsigned_keyword,
        signed_keyword,
        bool_keyword,
        complex_keyword,
        imaginary_keyword,
        balignas_keyword,
        balignof_keyword,
        asm_keyword,
        auto_keyword,
        break_keyword,
        case_keyword,
        const_keyword,
        continue_keyword,
        default_keyword,
        do_keyword,
        else_keyword,
        enum_keyword,
        extern_keyword,
        for_keyword,
        goto_keyword,
        if_keyword,
        register_keyword,
        return_keyword,
        sizeof_keyword,
        static_keyword,
        struct_keyword,
        switch_keyword,
        typedef_keyword,
        union_keyword,
        volatile_keyword,
        while_keyword,
        alignas_keyword,
        alignof_keyword,
        atomic_keyword,
        generic_keyword,
        noreturn_keyword,
        static_assert_keyword,
        thread_local_keyword,

        identifier,
        floating_point_literal,
        integer_literal,
        char_literal,
        string_literal,

        plus_assignment,
        minus_assignment,
        multiply_assignment,
        divide_assignment,
        modulus_assignment,
        bitwise_and_assignment,
        bitwise_or_assignment,
        bitwise_xor_assignment,
        shift_left_assignment,
        shift_right_assignment,
        shift_left,
        shift_right,
        equal,
        not_equal,
        less_than_or_equal,
        greater_than_or_equal,
        logical_and,
        logical_or,
        increment,
        decrement,
        plus,
        minus,
        multiply,
        divide,
        modulus,
        bitwise_and,
        bitwise_or,
        bitwise_xor,
        logical_not,
        bitwise_not,
        less_than,
        greater_than,
        conditional,
        assignment,
        colon,
        comma,
        dot,
        open_paren,
        close_paren,
        open_brace,
        close_brace,
        open_square_bracket,
        close_square_bracket,
        hash,
        at,
        dollar,
        semicolon };
        vector<string> types = {
        
        "INT_KEYWORD",
        "FLOAT_KEYWORD",
        "CHAR_KEYWORD",
        "VOID_KEYWORD",
        "DOUBLE_KEYWORD",
        "LONG_KEYWORD",
        "SHORT_KEYWORD",
        "UNSIGNED_KEYWORD",
        "SIGNED_KEYWORD",
        "BOOL_KEYWORD",
        "COMPLEX_KEYWORD",
        "IMAGINARY_KEYWORD",
        "ALIGNAS_KEYWORD",
        "ALIGNOF_KEYWORD",
        "ASM_KEYWORD",
        "AUTO_KEYWORD",
        "BREAK_KEYWORD",
        "CASE_KEYWORD",
        "CONST_KEYWORD",
        "CONTINUE_KEYWORD",
        "DEFAULT_KEYWORD",
        "DO_KEYWORD",
        "ELSE_KEYWORD",
        "ENUM_KEYWORD",
        "EXTERN_KEYWORD",
        "FOR_KEYWORD",
        "GOTO_KEYWORD",
        "IF_KEYWORD",
        "REGISTER_KEYWORD",
        "RETURN_KEYWORD",
        "SIZEOF_KEYWORD",
        "STATIC_KEYWORD",
        "STRUCT_KEYWORD",
        "SWITCH_KEYWORD",
        "TYPEDEF_KEYWORD",
        "UNION_KEYWORD",
        "VOLATILE_KEYWORD",
        "WHILE_KEYWORD",
        "ALIGNAS_KEYWORD",
        "ALIGNOF_KEYWORD",
        "ATOMIC_KEYWORD",
        "GENERIC_KEYWORD",
        "NORETURN_KEYWORD",
        "STATIC_ASSERT_KEYWORD",
        "THREAD_LOCAL_KEYWORD",

        "IDENTIFIER",
        "FLOATING_POINT_LITERAL",
        "INTEGER_LITERAL",
        "CHAR_LITERAL",
        "STRING_LITERAL",

        "PLUS_ASSIGNMENT",
        "MINUS_ASSIGNMENT",
        "MULTIPLY_ASSIGNMENT",
        "DIVIDE_ASSIGNMENT",
        "MODULUS_ASSIGNMENT",
        "BITWISE_AND_ASSIGNMENT",
        "BITWISE_OR_ASSIGNMENT",
        "BITWISE_XOR_ASSIGNMENT",
        "SHIFT_LEFT_ASSIGNMENT",
        "SHIFT_RIGHT_ASSIGNMENT",
        "SHIFT_LEFT",
        "SHIFT_RIGHT",
        "EQUAL",
        "NOT_EQUAL",
        "LESS_THAN_OR_EQUAL",
        "GREATER_THAN_OR_EQUAL",
        "LOGICAL_AND",
        "LOGICAL_OR",
        "INCREMENT",
        "DECREMENT",
        "PLUS",
        "MINUS",
        "MULTIPLY",
        "DIVIDE",
        "MODULUS",
        "BITWISE_AND",
        "BITWISE_OR",
        "BITWISE_XOR",
        "LOGICAL_NOT",
        "BITWISE_NOT",
        "LESS_THAN",
        "GREATER_THAN",
        "CONDITIONAL",
        "ASSIGNMENT",
        "COLON",
        "COMMA",
        "DOT",
        "OPEN_PAREN",
        "CLOSE_PAREN",
        "OPEN_BRACE",
        "CLOSE_BRACE",
        "OPEN_SQUARE_BRACKET",
        "CLOSE_SQUARE_BRACKET",
        "HASH",
        "AT",
        "DOLLAR",
        "SEMI_COLON" };


        string::const_iterator searchStart(code.cbegin());
        while (searchStart != code.cend())
        {
            // Skip over spaces
            while (searchStart != code.cend() && isspace(*searchStart)) {
                ++searchStart;
            }

            // Check if searchStart reached the end of code
            if (searchStart == code.cend()) {
                break;  // Exit the loop if end of code is reached
            }

            bool found = false;
            for (int i = 0; i < regexes.size(); ++i)
            {
                smatch match;
                if (regex_search(searchStart, code.cend(), match, regexes[i]) && match.prefix().length() == 0)
                {
                    tokens.push_back({ types[i], match.str() });
                    searchStart += match.length();
                    found = true;
                    break;  // we found a match so no need to check other patterns
                }
            }
            if (!found) {
                string invalidToken = "";
                invalidToken += *searchStart;
                tokens.push_back({ "ERROR", invalidToken });
                ++searchStart;
            }
        }

        return tokens;
    }
};


bool typeName();
void get_next_token();
bool expression();
bool genericSelection();
bool genericAssocList();
bool genericAssociation();
bool argumentExpressionList();
bool unaryOperator();
bool unaryExpression();
bool castExpression();
bool isTypeName(const Token& token);
bool postfixExpression();
bool assignmentExpression();
bool conditionalExpression();
bool assignmentOperator();
bool typeSpec();
bool declarator();
bool init_declarator();
bool init_declarator_list();
bool declaration_specifiers();
bool declaration();
bool blockItem();
bool blockItemList();
bool directDeclarator();
bool statement();
bool selection_statement();
bool iterative_statement();


int main() {

    string code = "if (X) int F; else int Y;";

    Lexer lexer;

    tokens = lexer.tokenize(code);

    for (auto token : tokens) {
        cout << token.type << " : " << token.value << endl;
    } 
    cout << endl << endl;
    cout << "SYMBOL TABLE" << endl;
    int i = 1 ;
    for (auto token : tokens) {
    bool flag = false;
        for (auto symbol : SymbolTable) {
			if (token.value == symbol) {
                flag = true;
                break;
			}
        }
        if (token.type == "IDENTIFIER" && !flag ) {
            cout << i << ") " << token.value << endl;
			SymbolTable.push_back(token.value);
            i++;
        }
    }
    cout << endl << endl;

    if (blockItemList()) {
        if (currentIndex >= tokens.size()) {
            cout << "Parsing successful!" << endl;
        }
        else {
            cout << "Parsing failed! Unexpected tokens remain." << endl;
        }
    }
    else {
        cout << "Parsing failed! Unable to parse expression." << endl;
    }

    return 0;
}

void get_next_token() {
    currentIndex++;
    stop++;
}

void get_prev_token() {
    currentIndex--;
}

bool assignmentExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (conditionalExpression()) {
        return true;
    }
    else if (unaryExpression()) {
        get_next_token();
        if (assignmentOperator()) {
            get_next_token();
            if (assignmentExpression()) {
                return true;
            }
        }
    }
    return false;
}

bool assignmentOperator() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    return tokenType == "ASSIGNMENT" || tokenType == "PLUS_ASSIGNMENT" ||
        tokenType == "MINUS_ASSIGNMENT" || tokenType == "MULTIPLY_ASSIGNMENT" ||
        tokenType == "DIVIDE_ASSIGNMENT" || tokenType == "MODULUS_ASSIGNMENT" ||
        tokenType == "SHIFT_LEFT_ASSIGNMENT" || tokenType == "SHIFT_RIGHT_ASSIGNMENT" ||
        tokenType == "BITWISE_AND_ASSIGNMENT" || tokenType == "BITWISE_OR_ASSIGNMENT" ||
        tokenType == "BITWISE_XOR_ASSIGNMENT";
}

bool genericAssocList() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (!genericAssociation()) {
        return false;
    }

    while (tokenType == "COMMA") {
        get_next_token();
        if (!genericAssociation()) {
            return false;
        }
    }

    return true;
}

bool unaryOperator() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "BITWISE_AND" || tokenType == "MULTIPLY" || tokenType == "PLUS" ||
        tokenType == "MINUS" || tokenType == "BITWISE_NOT" || tokenType == "LOGICAL_NOT") {
        get_next_token();
        return true;
    }
    return false;
}

bool isTypeName(const Token& token) {
    return token.type == "IDENTIFIER" || token.type == "TYPE_KEYWORD";
}

bool typeSpec() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "INT_KEYWORD" || tokenType == "FLOAT_KEYWORD" || tokenType == "CHAR_KEYWORD" || tokenType == "DOUBLE_KEYWORD") {
        get_next_token();
        return true;
    }
    else if (tokenType == "LONG_KEYWORD") {
        get_next_token();
        typeSpec();
        return true;
    }

    return false;
}

bool primaryExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "IDENTIFIER" || tokenType == "INTEGER_LITERAL" || tokenType == "STRING_LITERAL") {
        get_next_token();
        return true;
    }
    else if (tokenType == "OPEN_PAREN") {
        get_next_token();
        if (expression()) {
            if (tokenType == "CLOSE_PAREN") {
                get_next_token();
                return true;
            }
        }
    }
    else if (genericSelection()) {
        get_next_token();
        return true;
    }
    return false;
}

bool genericSelection() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "GENERIC_KEYWORD") {
        get_next_token();
        if (tokenType == "OPEN_PAREN") {
            get_next_token();
            if (assignmentExpression()) {
                if (tokenType == "COMMA") {
                    get_next_token();
                    if (genericAssocList()) {
                        if (tokenType == "CLOSE_PAREN") {
                            get_next_token();
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


bool typeName() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "INT_KEYWORD" || tokenType == "CHAR_KEYWORD" || tokenType == "DOUBLE_KEYWORD" || tokenType == "VOID_KEYWORD") {
        get_next_token();
        return true;
    }
    return false;
}

// Function to parse generic associations
bool genericAssociation() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (typeName()) {
        if (tokenType == "COLON") {
            get_next_token();
            if (assignmentExpression())
                return true;
        }
    }
    else if (tokenType == "DEFAULT_KEYWORD") {
        get_next_token();
        if (tokenType == "COLON") {
            get_next_token();
            if (assignmentExpression())
                return true;
        }
    }
    // Handle other cases if needed
    return false;
}

// Function to parse postfix expressions
bool postfixExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (primaryExpression()) {
        while (true) {
            if (tokenType == "OPEN_SQUARE_BRACKET") {
                get_next_token();
                if (!expression())
                    return false;
                if (tokenType == "CLOSE_SQUARE_BRACKET")
                    get_next_token();
                else
                    return false;
            }
            else if (tokenType == "OPEN_PAREN") {
                get_next_token();
                if (argumentExpressionList()) {
                    if (tokenType == "CLOSE_PAREN")
                        get_next_token();
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tokenType == "DOT" || tokenType == "ARROW") {
                get_next_token();
                if (tokenType == "IDENTIFIER")
                    get_next_token();
                else
                    return false;
            }
            else if (tokenType == "INCREMENT" || tokenType == "DECREMENT") {
                get_next_token();
            }
            else {
                break;
            }
        }
        return true;
    }
    // Handle other cases if needed
    return false;
}

bool argumentExpressionList() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (!assignmentExpression()) {
        return false;
    }

    while (tokenType == "COMMA") {
        get_next_token();
        if (!assignmentExpression()) {
            return false;
        }
    }

    return true;
}

// Function to parse unary expressions
bool unaryExpression() {
	if (currentIndex >= tokens.size()) {
		return false;
	}
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "INCREMENT" || tokenType == "DECREMENT") {
        get_next_token();
        if (unaryExpression())
            return true;
    }
    else if (unaryOperator()) {
        if (castExpression())
            return true;
    }
    else if (tokenType == "SIZEOF_KEYWORD") {
        get_next_token();
        if (tokenType == "OPEN_PAREN") {
            get_next_token();
            if (typeName()) {
                if (tokenType == "CLOSE_PAREN") {
                    get_next_token();
                    return true;
                }
            }
        }
        else if (unaryExpression()) {
            return true;
        }
    }
    else if (tokenType == "_Alignof") {
        get_next_token();
        if (tokenType == "OPEN_PAREN") {
            get_next_token();
            if (typeName()) {
                if (tokenType == "CLOSE_PAREN") {
                    get_next_token();
                    return true;
                }
            }
        }
    }
    else if (postfixExpression()) {
        return true;
    }
    return false;
}

bool castExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (unaryExpression()) {
        return true;
    }
    else if (tokenType == "OPEN_PAREN") {
        get_next_token();
        if (typeName()) {
            if (tokenType == "CLOSE_PAREN") {
                get_next_token();
                if (castExpression()) {
                    return true;
                }
            }
            else {
                // Error: Expected a closing parenthesis
                return false;
            }
        }
        else {
            // Error: Expected a type name after '('
            return false;
        }
    }
    return false; // Not a valid castExpression
}


bool multiplicativeExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (castExpression()) {
        while (tokenType == "MULTIPLY" || tokenType == "DIVIDE" || tokenType == "MODULUS")
        {
            get_next_token();
            if (!castExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse additive expressions
bool additiveExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (multiplicativeExpression()) {
        while (tokenType == "PLUS" || tokenType == "MINUS")
        {
            get_next_token();
            if (!multiplicativeExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse shift expressions
bool shiftExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (additiveExpression()) {
        while (tokenType == "SHIFT_LEFT" || tokenType == "SHIFT_RIGHT")
        {
            get_next_token();
            if (!additiveExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse relational expressions
bool relationalExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (shiftExpression()) {
        while (tokenType == "LESS_THAN" || tokenType == "GREATER_THAN" ||
            tokenType == "LESS_THAN_OR_EQUAL" || tokenType == "GREATER_THAN_OR_EQUAL")
        {
            get_next_token();
            if (!shiftExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse equality expressions
bool equalityExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (relationalExpression()) {
        while (tokenType == "EQUAL" || tokenType == "NOT_EQUAL")
        {
            get_next_token();
            if (!relationalExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse AND expressions
bool andExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (equalityExpression()) {
        while (tokenType == "BITWISE_AND")
        {
            get_next_token();
            if (!equalityExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse exclusive OR expressions
bool exclusiveOrExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (andExpression()) {
        while (tokenType == "BITWISE_XOR")
        {
            get_next_token();
            if (!andExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse inclusive OR expressions
bool inclusiveOrExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (exclusiveOrExpression()) {
        while (tokenType == "BITWISE_OR")
        {
            get_next_token();
            if (!exclusiveOrExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse logical AND expressions
bool logicalAndExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (inclusiveOrExpression()) {
        while (tokenType == "LOGICAL_AND")
        {
            get_next_token();
            if (!inclusiveOrExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse logical OR expressions
bool logicalOrExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (logicalAndExpression()) {
        while (tokenType == "LOGICAL_OR")
        {
            get_next_token();
            if (!logicalAndExpression())
                return false;
        }
        return true;
    }
    return false;
}

// Function to parse conditional expressions
bool conditionalExpression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (logicalOrExpression()) {
        if (tokenType == "CONDITIONAL") {
            get_next_token();
            if (expression()) {
                if (tokenType == "COLON") {
                    get_next_token();
                    if (conditionalExpression())
                        return true;
                }
            }
        }
        else {
            return true;
        }
    }
    return false;
}

bool expression() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;

    if (assignmentExpression()) {
		get_next_token();
        while (tokenType == "COMMA") {
            get_next_token();
            if (!assignmentExpression())
                return false;
        }
        return true;
    }
    return false;
}

bool declaration() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    if (declaration_specifiers()) {
        if (init_declarator_list()) {
            return true;
        }
    }
    else if (declaration_specifiers()) {
        return true;
    }
    return false;
}

bool declaration_specifiers() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    if (typeSpec()) {
        if (!declaration_specifiers()) {
            get_prev_token();
        }
        else if (declaration_specifiers())
            return true;
    }
    if (typeSpec()) {
        return true;
    }
    return false;
}
bool init_declarator_list() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    if (init_declarator()) {
        return true;
    }
    else if (init_declarator_list()) {
        return true;
    }
    return false;
}
bool init_declarator() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    if (declarator())
        return true;
	return false;
}
bool declarator() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (directDeclarator()) {
        get_next_token();
        return true;
    }
	return false;
}

bool directDeclarator() {
	if (currentIndex >= tokens.size()) {
		return false;
	}
	string tokenType = tokens[currentIndex].type;
	if (tokenType == "IDENTIFIER") {
		get_next_token();
        if (currentIndex >= tokens.size()) {
            get_prev_token();
        }
        tokenType = tokens[currentIndex].type;
		if (tokenType == "OPEN_PAREN") {
            get_next_token();
            if (currentIndex >= tokens.size()) {
                get_prev_token();
            }
            tokenType = tokens[currentIndex].type;
			if (tokenType == "CLOSE_PAREN") {
				get_next_token();
				return true;
			}
		}
	}
    get_prev_token();
    tokenType = tokens[currentIndex].type;
    if (tokenType == "IDENTIFIER") {
        if (currentIndex >= tokens.size()) {
            return false;
        }
        get_next_token();
        tokenType = tokens[currentIndex].type;
        if (tokenType == "SEMI_COLON") {
            get_next_token();
            return true;
        }
    }
	return false;

}

bool statement() {
    if (currentIndex >= tokens.size()) {
        return false;
    }

    if (selection_statement()) {
        get_next_token();
        return true;
    }
    if (iterative_statement()) {
        get_next_token();
        return true;
    }

}

bool iterative_statement() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "WHILE_KEYWORD") {
        if (currentIndex >= tokens.size()) {
            get_prev_token();
        }
        get_next_token();
        tokenType = tokens[currentIndex].type;
        if (tokenType == "OPEN_PAREN") {
            if (currentIndex >= tokens.size()) {
                get_prev_token();
            }
            get_next_token();
            tokenType = tokens[currentIndex].type;
            if (expression()) {
                if (currentIndex >= tokens.size()) {
                    get_prev_token();
                }
                get_prev_token();
                tokenType = tokens[currentIndex].type;
                if (tokenType == "CLOSE_PAREN") {
                    if (currentIndex >= tokens.size()) {
                        get_prev_token();
                    }
                    get_next_token();
                    tokenType = tokens[currentIndex].type;
                    if (expression()) {
                        get_next_token();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool selection_statement() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    string tokenType = tokens[currentIndex].type;
    if (tokenType == "IF_KEYWORD") {
        if (currentIndex >= tokens.size()) {
            get_prev_token();
        }
        get_next_token();
        tokenType = tokens[currentIndex].type;
        if (tokenType == "OPEN_PAREN") {
            if (currentIndex >= tokens.size()) {
                get_prev_token();
            }
            get_next_token();
            tokenType = tokens[currentIndex].type;
            if (expression()) {
                if (currentIndex >= tokens.size()) {
                    get_prev_token();
                }
                get_prev_token();
                tokenType = tokens[currentIndex].type;
                if (tokenType == "CLOSE_PAREN") {
                    if (currentIndex >= tokens.size()) {
                        get_prev_token();
                    }
                    get_next_token();
                    tokenType = tokens[currentIndex].type;
                    if (declaration()) {
                        if (currentIndex >= tokens.size()) {
                            get_prev_token();
                        }
                        get_prev_token();
                        tokenType = tokens[currentIndex].type;
                        if (tokenType == "ELSE_KEYWORD") {
                            if (currentIndex >= tokens.size()) {
                                get_prev_token();
                            }
                            get_next_token();
                            tokenType = tokens[currentIndex].type;
                            if (declaration()) {
                                get_next_token();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool blockItemList() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
	if (blockItem()) {
		if (stop < tokens.size()) {
            for (int i = currentIndex; i > 0; i--) {
                get_prev_token();
            }
		}
        else
		    return true;
	}
    else if (blockItemList()) {
         get_prev_token();
         if (blockItem())
             return true;
	}
	return false;
}

bool blockItem() {
    if (currentIndex >= tokens.size()) {
        return false;
    }
    if (statement()) {
        if (stop < tokens.size()) {
            return false;
        }
        return true;
    }
    else if (expression()) {
        if (stop < tokens.size()) {
            return false;
        }
        return true;
    }
    else if (declaration()) {
        if (stop < tokens.size()) {
            return false;
        }
        return true;
    }
	return false;
}