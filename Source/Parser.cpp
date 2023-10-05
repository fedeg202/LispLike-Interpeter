
#include <iostream>

#include "Parser.h"
#include "Token.h"



Program* P_Parser::operator()(const std::vector<Token>& tokenStream)
{
    auto tokenItr = tokenStream.begin();
    streamEnd = tokenStream.end();
    if (tokenItr != streamEnd) {
        Block* block = Block_Parser(tokenItr);
        safe_next(tokenItr);
        if (tokenItr != streamEnd) throw ParseError("Error in " + tokenItr->word + " ");
        Program* program = new Program(block);
        return program;
    }
    else {
        throw ParseError("Empty program");
        return NULL;
    }
}

//parsing function for blocks
//Idea: the block contains only one statement or contains "BLOCK" instruction
Block* P_Parser::Block_Parser(std::vector<Token>::const_iterator& Itr)
{
    Block* block = NULL;
    if (Itr->tag == Token::LP) {
        std::vector<Statement*> stmt;
        safe_next(Itr);
        block = Bm.makeBlock(stmt);
        if (Itr->tag == Token::BLOCK) {
            //contains BLOCK instruction
            safe_next(Itr);
            while (Itr->tag != Token::RP) {
                block->add_Statement(S_Parser(Itr));
                Itr++;
                if (Itr == streamEnd) {
                    throw ParseError("Mismatching parenthesis in block statement");
                }
            }
            if (block->getSize()<1) throw ParseError("Empty block statement");
            if (Itr->tag == Token::RP) {
                return block;
            }
            else throw ParseError("Generic parsing error at token :" + Itr->word);
        }
        else if (Itr->tag > 2 && Itr->tag < 8) {
            //contains only one statement
            Itr--;
            block->add_Statement(S_Parser(Itr));
            if (Itr == streamEnd) throw ParseError("Unexpected end");
            else if (Itr->tag == Token::RP) {
                return block;
            }
            else throw ParseError("Mismatching parenthesis at token: " + Itr->word);

        }
        else throw ParseError("Wrong block statement at token: " + Itr->word);
    }
    else throw ParseError("Mismatching parenthesis at token: " + Itr->word );
   
    return block;
}

//parsing function for numeric expressions
//Idea: start with "(" and end with ")" and contains an operator or it's a number or it's a Variable
NumExpr* P_Parser::NExpr_Parser(std::vector<Token>::const_iterator& Itr)
{
    if (Itr->tag == Token::LP) {
        //start with "(" so must contains an operator and end with ")"
        safe_next(Itr);
        if (Itr->tag == Token::ADD) {
            //ADD operator
            Operator::Opcode op;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            op = Operator::ADD;
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in ADD numeric expression");
            if (Itr->tag == Token::RP) {
                return Bm.get_Nem().makeOperator(op, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Wrong add numeric expression sintax at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::SUB) {
            //SUB operator
            Operator::Opcode op;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            op = Operator::SUB;
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in SUB numeric expression");
            if (Itr->tag == Token::RP) {
               //check that end with ")"
                return Bm.get_Nem().makeOperator(op, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Wrong sub numeric expression sintax at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::MUL) {
            //MUL operator
            Operator::Opcode op;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            op = Operator::MUL;
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in MUL numeric expression");
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Nem().makeOperator(op, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Wrong mul numeric expression sintax at token: " + Itr->word);
            }
           
        }


        else if (Itr->tag == Token::DIV) {
            //DIV operator
            Operator::Opcode op;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            op = Operator::DIV;
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in DIV numeric expression");
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Nem().makeOperator(op, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Wrong div numeric expression sintax at token: " + Itr->word);
            }
        }
        else {
            throw ParseError("Unrecognised operator at token: " + Itr->word);
        }
    }


    else if (Itr->tag == Token::NUM) {
        //it's a number
         return Bm.get_Nem().makeNumber(std::stoi(Itr->word));
    }


    else if (Itr->tag == Token::VID) {
        //it's a variable
        return Bm.get_Nem().makeVariable(Itr->word);
    }


    else throw ParseError("Wrong numeric expression syntax at token :" + Itr->word);
}

//parsing function for statements
//Idea: statements start with "(" and end with ")" and contains an instruction
Statement* P_Parser::S_Parser(std::vector<Token>::const_iterator& Itr)
{
  if (Itr->tag == Token::LP) {
        safe_next(Itr);
        if (Itr->tag == Token::SET) {
            //SET istruction
            safe_next(Itr);
            if (Itr->tag == Token::VID) {
                Variable* var = Bm.get_Nem().makeVariable(Itr->word);
                safe_next(Itr);
                NumExpr* num_expr = NExpr_Parser(Itr);
                safe_next(Itr);
                if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in SET statement");
                if (Itr->tag == Token::RP) {
                    //check that end with ")"
                    return Bm.get_Sm().makeSetStmt(var, num_expr);
                }
                else throw ParseError("Mismatching parenthesis at token:" + Itr->word);
            }
            else throw ParseError("Wrong variable definition sintax at token: " + Itr->word);
        }


        else if (Itr->tag == Token::PRINT) {
            //PRINT istruction
            safe_next(Itr);
            NumExpr* num_expr = NExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in a PRINT statement");
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Sm().makePrintStmt(num_expr);
            }
            else throw ParseError("Mismatching parenthesis at token: " + Itr->word);
        }


        else if (Itr->tag == Token::INPUT) {
            //INPUT istruction
            safe_next(Itr);
            if (Itr->tag == Token::VID) {
                Variable* var = Bm.get_Nem().makeVariable(Itr->word);
                safe_next(Itr);
                if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in INPUT statement");
                if (Itr->tag == Token::RP) {
                    //check that end with ")"
                    return Bm.get_Sm().makeInputStmt(var);
                }
                else throw ParseError("Mismatching parenthesis at token: " + Itr->word);
                
            }
            else throw ParseError("Wrong input statement sintax at token: " + Itr->word);
        }


        else if (Itr->tag == Token::IF) {
            //IF istruction
            safe_next(Itr);
            BoolExpr* bool_expr = BExpr_Parser(Itr);
            safe_next(Itr);
            Block* block1 = Block_Parser(Itr);
            safe_next(Itr);
            Block* block2 = Block_Parser(Itr);
            safe_next(Itr);
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in IF statement");
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Sm().makeIfStmt(bool_expr, block1, block2);
            }
            else throw ParseError("Mismatching parenthesis at token: " + Itr->word);
        }


        else if (Itr->tag == Token::WHILE) {
            //WHILE istruction
            safe_next(Itr);
            BoolExpr* bool_expr = BExpr_Parser(Itr);
            safe_next(Itr);
            Block* block = Block_Parser(Itr);
            safe_next(Itr);
            if (Itr == streamEnd) throw ParseError("Mismatching parenthesis in a WHILE statement");
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Sm().makeWhileStmt(bool_expr, block);
            }
            else throw ParseError("Mismatching parenthesis at token: " + Itr->word);
        }


        else {
            throw ParseError("Unrecognised instruction at token: " + Itr->word);
        }
        
    }
    else if (Itr->tag == Token::RP) throw ParseError("Missing statement at token: " + Itr->word);


    else throw ParseError("Missing openening parenthesis at token: " + Itr->word);
}

//parsing function for boolean expression
//Idea: boolean expression start with "(" and end with ")" and contain an operator or are a boolean constatnt
BoolExpr* P_Parser::BExpr_Parser(std::vector<Token>::const_iterator& Itr)
{
    if (Itr->tag == Token::LP) {
        safe_next(Itr);
        if (Itr->tag == Token::LT) {
            //LT operator
            RelOp::RelOpcode rop = RelOp::LT;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeRelOp(rop, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Mismatching parenthesis at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::GT) {
            //GT operator
            RelOp::RelOpcode rop = RelOp::GT;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeRelOp(rop, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Mismatching parenthesis at token: " + Itr->word);          
            }
        }


        else if (Itr->tag == Token::EQ) {
            //EQ operator
            RelOp::RelOpcode rop = RelOp::EQ;
            safe_next(Itr);
            NumExpr* num_expr1 = NExpr_Parser(Itr);
            safe_next(Itr);
            NumExpr* num_expr2 = NExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeRelOp(rop, num_expr1, num_expr2);
            }
            else {
                throw ParseError("Mismatching parenthesis at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::AND) {
            //AND operator
            BoolOp::BoolOpcode bop = BoolOp::AND;
            safe_next(Itr);
            BoolExpr* bool_expr1 = BExpr_Parser(Itr);
            safe_next(Itr);
            BoolExpr* bool_expr2 = BExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeBoolOp(bop, bool_expr1, bool_expr2);
            }
            else {
                throw ParseError("Mismatching parentesis at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::OR) {
            //OR operator
            BoolOp::BoolOpcode bop = BoolOp::OR;
            safe_next(Itr);
            BoolExpr* bool_expr1 = BExpr_Parser(Itr);
            BoolExpr* bool_expr2 = BExpr_Parser(Itr);
            
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeBoolOp(bop, bool_expr1, bool_expr2);
            }
            else {
                throw ParseError("Mismatching parentesis at token: " + Itr->word);
            }
        }


        else if (Itr->tag == Token::NOT) {
            //NOT operator
            safe_next(Itr);
            BoolExpr* bool_expr = BExpr_Parser(Itr);
            safe_next(Itr);
            if (Itr->tag == Token::RP) {
                //check that end with ")"
                return Bm.get_Bem().makeNotOp(bool_expr);
            }
            else {
                throw ParseError("Mismatching parentesis at token: " + Itr->word);
            }
        }


        else {
            throw ParseError("Unrecognised Bool or Relation operator at token: " + Itr->word);
        }
    }


    else if (Itr->tag == Token::RP) {
        throw ParseError("Missing opening parenthesis at token: " + Itr->word);
    }


    else if (Itr->tag == Token::FALSE) {
        //boolean constant FALSE
        return Bm.get_Bem().makeBoolConst(false);
    }


    else if (Itr->tag == Token::TRUE) {
        //boolean constant TRUE
        return Bm.get_Bem().makeBoolConst(true);
    }


    else throw ParseError("Wrong boolean expression syntax at token: " + Itr->word);
}
