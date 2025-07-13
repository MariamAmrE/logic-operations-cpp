#include<iostream>
#include<string>
#include<stack>

using namespace std;

//this function converts infix into post fix using stack
//for example input: (A&B&!C)  --> output: AB&C!&
string infix_to_postfix(string infix)
{
    string postfix = infix;
    int j=0;
    stack<char>s_postfix;
    for(int i = 0; i<(int)infix.length(); i++)
    {
        switch(infix[i])
        {
//=========================

        case '!':
            s_postfix.push('!');
            break;
//=========================

        case '&':
            if(!s_postfix.empty())
            {
                while(s_postfix.top() == '!'  || s_postfix.top() == '!')
                {
                    postfix[j++] = s_postfix.top();
                    s_postfix.pop();
                    if(s_postfix.empty())break;

                }
                s_postfix.push('&');

            }
            else
                s_postfix.push('&');
            break;
//=========================

        case '|':
            if(!s_postfix.empty())
            {
                while(s_postfix.top() == '!' || s_postfix.top() == '&' || s_postfix.top() == '|')
                {
                    postfix[j++] = s_postfix.top();
                    s_postfix.pop();
                    if(s_postfix.empty())break;
                }
                s_postfix.push('|');
            }
            else
                s_postfix.push('|');
            break;
//=========================

        case '(':
            s_postfix.push('(');
            break;
//=========================

        case ')':
            while(s_postfix.top() != '(')
            {
                postfix[j++]= s_postfix.top();
                s_postfix.pop();
            }
            s_postfix.pop();
            break;
//=========================

        case 'A':
            postfix[j++] = infix[i];
            break;
//=========================

        case 'B':
            postfix[j++] = infix[i];
            break;
//=========================
        case 'C':
            postfix[j++] = infix[i];
            break;
//=========================
        case '0':
            postfix[j++] = infix[i];
            break;
//=========================
        case '1':
            postfix[j++] = infix[i];
            break;
//=========================
        default:
            break;
        }

    }
    while(!s_postfix.empty())
    {
        postfix[j++]=s_postfix.top();
        s_postfix.pop();
    }

    return postfix.substr(0, j);
}





//this function evaluate the postfix to do operations on variable in correct order using stack: for example AB&C!&
//|______|     |_____|     |     |      |_______|
//|___B__|  &  |__C__|  !  |_!C__|  &   |_______|
//|___A__| --> |_A&B_| --> |_A&B_| -->  |_A&B&!C|
//===================================================================================
void evaluatingPostfix(string postfix, bool A[8], bool B[8], bool C[8], bool output[8])
{
    stack<bool>s_evaluatePostfix;
    bool partOfExpression; //shows stages of evaluation in stack
    for(int i = 0; i<8 ; i++)  //8 is the number of combinations of ABC --> 2**3
    {
        for(int j = 0; j<(int)postfix.length(); j++)
        {
            switch(postfix[j])
            {
            case 'A':
                s_evaluatePostfix.push(A[i]);
                break;

            case 'B':
                s_evaluatePostfix.push(B[i]);
                break;

            case 'C':
                s_evaluatePostfix.push(C[i]);
                break;

            case '0':
                s_evaluatePostfix.push(0);
                break;

            case '1':
                s_evaluatePostfix.push(1);
                break;

            case '!':
                partOfExpression = !s_evaluatePostfix.top();
                s_evaluatePostfix.pop();
                s_evaluatePostfix.push(partOfExpression);
                break;

            case '&':
                partOfExpression = s_evaluatePostfix.top();
                s_evaluatePostfix.pop();
                partOfExpression = partOfExpression && s_evaluatePostfix.top();
                s_evaluatePostfix.pop();
                s_evaluatePostfix.push(partOfExpression);
                break;

            case '|':
                partOfExpression = s_evaluatePostfix.top();
                s_evaluatePostfix.pop();
                partOfExpression = partOfExpression || s_evaluatePostfix.top();
                s_evaluatePostfix.pop();
                s_evaluatePostfix.push(partOfExpression);
                break;

            default:
                break;

            }

        }

        output[i] = s_evaluatePostfix.top();
        s_evaluatePostfix.pop();
    }

}


//===================================================================================
void printTruthTable(bool output[8],bool A[8],bool B[8],bool C[8], string expression)
{



    cout << "***the truth table of the expression: "<<expression<<" is: \n"<< endl;
    cout << "A  " << "B  " << "C  " << "output" << endl;
    cout << "______________" << endl;
    for(int i =0; i <8; i++)
    {

        /*printing the truth table(each row is printed containing the inputs A,B,C and the result)*/
        cout << A[i] << "  " << B[i] << "  " << C[i] << "    " <<  output[i]<< endl;
    }
    cout << "\n";
    cout<<"======================================================================================================================\n\n";



}
//========================================================================================================


void checkEquivalenceOfTheExpressions(bool originalExpressionOutput[8],bool simplifiedExpressionOutput[8])
{
    /*this variable is used as a flag
     *  and if the two outputs are not equivalent,then it will be changed to false
     *  ,in addition, the loop will be left*/
    bool isEquivalent = true;

    for(int i = 0; i <8; i++)
    {
        if(originalExpressionOutput[i] != simplifiedExpressionOutput[i])
        {
            isEquivalent=false;
            break;
        }
    }
    if(isEquivalent)
    {
        cout << "\"CONGRATS :D !THE TWO EXPRESSIONS ARE EQUIVALENT.\"\n";
    }
    else
    {
        cout << "\"SORRY :'(, THE TWO EXPRESSIONS AREN'T EQUIVALENT\"\n";
    }
    cout<<"\n";
    cout<<"======================================================================================================================\n\n";

}

//======================================================================================

void getInputsOfSatisfiability(bool *A,bool*B,bool*C,bool output[8], string expression)
{

    cout << "***the inputs that make the expression  " <<expression << "    satisfiable ( equals 1) are: \n"<<endl;
    cout << "A  " << "B  " << "C  " << endl;
    cout << "__________" << endl;
    int noOfCombinationsSatisfyEquation = 0; //A flag to check if the expression is contradiction or tautology;
    for(int i =0; i < 8; i++)
    {
        /*checking if the output = 1*/
        if(output[i])
        {
            cout << A[i] << "  " << B[i] << "  " << C[i] << endl;
            noOfCombinationsSatisfyEquation += 1;
        }
    }

    if(noOfCombinationsSatisfyEquation == 0)
    {
        cout<<"\n*Expression is representing a contradiction\n"<<endl;
        cout<<"======================================================================================================================\n\n";
    }
    else if( noOfCombinationsSatisfyEquation == 8)
    {
        cout<<"\n*Expression is representing a tautology\n"<<endl;
        cout<<"======================================================================================================================\n\n";
    }
    else
    {
        cout<<"\n*The expression is NOT representing a tautology or a contradiction*\n"<<endl;
        cout<<"======================================================================================================================\n\n";
    }
}
//======================================================================================
void userInstructions()
{

    cout<<"***Please Enter expressions according to these rules:\n";
    cout<<"   1)Do NOT leave any spaces\n";
    cout<<"   2)DO NOT use any other variable except A , B and C ,also lower case is NOT allowed\n";
    cout<<"   3)Enter expressions in logical form using & for AND , | for OR , ! for NOT gates\n";
    cout<<"*for example: if you want to Enter the expression: (A B C'  +  A B C)' then Enter: !((A&B&!C)|(A&B&C))\n";
    cout<<"         ,and if you want to Enter the simplified expression: (AB)' then Enter: !(A&B) .\n";
    cout<<"*note: You are free to use brackets in any way that's logical.\n\n";
    cout<<"======================================================================================================================\n\n";


}

//======================================================================================
void takeUserInput(string &expression, string &simplifiedExpression)
{
    bool validExpression = true;
    bool validSimplifiExpression = true ;
    cout<<"***Enter boolean Expression:\n";
    do
    {
        cin>>expression;
        for(int i=0; i<(int)expression.length() ; i++)
        {
            if(!(expression[i]=='A')&&!(expression[i]=='B')&&!(expression[i]=='C')&&!(expression[i]=='(')&&!(expression[i]==')')&&!(expression[i]=='!')&&!(expression[i]=='|')&&!(expression[i]=='&')&&!(expression[i]=='0')&&!(expression[i]=='1'))
            {
                validExpression = false;
            }

        }
        if(!validExpression)
            cout<<"invalid expression! Please enter expression according to the rules"<<endl;

    }
    while(!validExpression);


    cout<<endl<<"***Enter simplified Expression:\n";
    do
    {
        cin>>simplifiedExpression;
        for(int i=0; i<(int)simplifiedExpression.length() ; i++)
        {
            if(!(simplifiedExpression[i]=='A')&&!(simplifiedExpression[i]=='B')&&!(simplifiedExpression[i]=='C')&&!(simplifiedExpression[i]=='(')&&!(simplifiedExpression[i]==')')&&!(simplifiedExpression[i]=='!')&&!(simplifiedExpression[i]=='|')&&!(simplifiedExpression[i]=='&')&&!(simplifiedExpression[i]=='0')&&!(simplifiedExpression[i]=='1'))
            {
                validSimplifiExpression = false;
            }

        }
        if(!validSimplifiExpression)
            cout<<"invalid expression! Please enter expression according to the rules"<<endl;

    }
    while(!validSimplifiExpression);

    cout<<"======================================================================================================================\n\n";

}

//=======================================================================================








int main()
{
    bool A[8] = {0,0,0,0,1,1,1,1};
    bool B[8] = {0,0,1,1,0,0,1,1};
    bool C[8] = {0,1,0,1,0,1,0,1};
    bool output[8];
    bool simplified_output[8];
    string expression;
    string simplifiedExpression;
    userInstructions();
    takeUserInput(expression, simplifiedExpression);
    //evaluating infix to convert it to postfix to decide the operations correct order
    //passing the infix_to_postfix function output to evaluatingPostfix function which
    //do the operations in the right order according to postfix to every combination of inputs we have
    evaluatingPostfix(infix_to_postfix(expression), A, B, C, output);
    evaluatingPostfix(infix_to_postfix(simplifiedExpression), A, B, C, simplified_output);
    //printing the truth table of original expression
    printTruthTable(output, A, B, C,expression);
    //printing the truth table of simplified expression
    printTruthTable(simplified_output, A, B, C,simplifiedExpression);
    //checking equivalence of the simplified expression and the original one
    checkEquivalenceOfTheExpressions(output, simplified_output);
    //getting inputs that satisfy the original equation
    getInputsOfSatisfiability(A,B,C,output,expression );
    //getting inputs that satisfy the simplified equation;
    getInputsOfSatisfiability(A,B,C,simplified_output, simplifiedExpression);


    //if there are a contradiction or tautology change one gate and repeat the steps:
    while(((output[0]&&output[1]&&output[2]&&output[3]&&output[4]&&output[5]&&output[6]&&output[7])==1) || ((output[0]||output[1]||output[2]||output[3]||output[4]||output[5]||output[6]||output[7]) == 0))
    {
        bool changeGate; //a flag that's when raised change one gate and repeat
        cout<<"1:Change one gate and repeat\n0:Exit"<<endl;
        cin>>changeGate;
        if(!changeGate) break; //if the user chose 1 the program will finish execution and we will exit
        takeUserInput(expression, simplifiedExpression);
        evaluatingPostfix(infix_to_postfix(expression), A, B, C, output);
        evaluatingPostfix(infix_to_postfix(simplifiedExpression), A, B, C, simplified_output);
        printTruthTable(output, A, B, C,expression);
        printTruthTable(simplified_output, A, B, C,simplifiedExpression);
        checkEquivalenceOfTheExpressions(output, simplified_output);
        getInputsOfSatisfiability(A,B,C,output,expression );
        getInputsOfSatisfiability(A,B,C,simplified_output, simplifiedExpression);
    }
    cout<<"THANK YOU!"<<endl;

    return 0;
}

