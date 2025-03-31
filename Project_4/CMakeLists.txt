cmake_minimum_required(VERSION 3.21)
project(Project_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_4 main.cpp Parser.h Predicate.h Token.h DatalogProgram.h Rule.h Parameter.h Scanner.h Scheme.h Tuple.h Relation.h Database.h Interpreter.h)
