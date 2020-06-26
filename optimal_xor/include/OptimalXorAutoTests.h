//
// Created by barak on 25/06/2020.
//

#ifndef AILABGENETICALGORITHM_OPTIMALXORAUTOTESTS_H
#define AILABGENETICALGORITHM_OPTIMALXORAUTOTESTS_H

void testRightRightDepth1();

#include <iostream>
#include <string>
#include "ExpressionTree.h"

void assertPropertyCalculatedCorrectly(const int expected, const int actual, bool &isFine) {
    if (expected != actual) {
        std::cout << "ERROR, expected: " << expected << ", actual:" << actual << std::endl;
        isFine = false;
    }
}

void testTree(const std::string treeAsString, const int expectedHeight, bool quietMode = false,
              const std::vector<bool> &expectedTruthTableRes = {}) {
    bool isFine = true;
    ExpressionTree exprTree{treeAsString, 0, expectedHeight};
    assertPropertyCalculatedCorrectly(expectedHeight, exprTree.getTreeHeight(), isFine);
    if (!quietMode)
        exprTree.print();

    // Doing it because printing truth table for a tree without operands is useless
    if (exprTree.getNumberOfOperands() > 0) {
        if (!quietMode)
            exprTree.printTruthTable();
        const auto actualTruthTableRes = exprTree.getEvaluatedResults();
        if (actualTruthTableRes != expectedTruthTableRes) {
            std::cout << "ERROR, evaluated results are different.. EXITING APPLICATION" << std::endl;
            isFine = false;
        } else {
            if (!quietMode) {
                std::cout << "No meaning to look at the table, it's fine!" << std::endl;
                std::cout << "==================" << std::endl;
            }
        }
    }

    isFine = isFine && exprTree.isOK();
    if (!isFine) {
        std::cout << "failed parsing the following string tree: " << treeAsString << std::endl;
        exit(-1);
    }
}

void testSwappingTrees(const std::string &treeOne, const int treeOneMaxDepth, std::vector<bool> treeOneExpectedResult,
                       const std::string &treeTwo, const int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedResult,
                       const int swapDepth) {
    ExpressionTree a{treeOne, 0, treeOneMaxDepth};
    ExpressionTree b{treeTwo, 0, treeTwoMaxDepth};
    a.treeCrossover(b, swapDepth);
    const auto actualTreeAcalculatedResults = a.getEvaluatedResults();
    const auto actualTreeBcalculatedResults = b.getEvaluatedResults();
    bool isOK = true;
    if (actualTreeAcalculatedResults != treeOneExpectedResult) {
        std::cout << "results comparison for tree one has failed :(" << std::endl;
        isOK = false;
    }
    if (actualTreeBcalculatedResults != treeTwoExpectedResult) {
        std::cout << "results comparison for tree one has failed :(" << std::endl;
        isOK = false;
    }
    isOK = isOK && a.isOK() && b.isOK();
    if (!isOK) {
        std::cout << "Tree swap failed.. " << std::endl;
        exit(-1);
    }
}

void testSwawppingRootFuncForTreeInDepthOne(std::string treeAsStringOne,
                                            std::string treeAsStringTwo,
                                            std::vector<bool> expectedResultForTreeOne,
                                            std::vector<bool> expectedResultForTreeTwo) {
    ExpressionTree aT{treeAsStringOne, 0, 1};
    ExpressionTree bT{treeAsStringTwo, 0, 1};
    aT.treeCrossover(bT, 0);
    bool isOK = true;
    if (expectedResultForTreeOne != aT.getEvaluatedResults()) {
        std::cout << "ERROR, tree 1 evaluated false" << std::endl;
        isOK = false;
    }
    if (expectedResultForTreeTwo != bT.getEvaluatedResults()) {
        std::cout << "ERROR, tree 2 evaluated false" << std::endl;
        isOK = false;
    }
    isOK = isOK && aT.isOK() && bT.isOK();


    if (!isOK)
        exit(-1);
}

void testSwappingTreesTerminals(std::string treeAsStringOne,
                                std::string treeAsStringTwo,
                                std::vector<char> treeOneTerminals,
                                std::vector<char> treeTwoTerminals) {
    ExpressionTree aT{treeAsStringOne, 0, 0};
    ExpressionTree bT{treeAsStringTwo, 0, 0};
    bool isOK = true;
    if (treeOneTerminals != aT.getAllOperands()) {
        std::cout << "ERROR, tree 1 has different operands than expected" << std::endl;
        isOK = false;
    }
    if (treeTwoTerminals != bT.getAllOperands()) {
        std::cout << "ERROR, tree 2 has different operands than expected" << std::endl;
        isOK = false;
    }
    aT.treeCrossover(bT, 0);

    if (treeTwoTerminals != aT.getAllOperands()) {
        std::cout << "ERROR, tree 1 has different operands than expected" << std::endl;
        isOK = false;
    }
    if (treeOneTerminals != bT.getAllOperands()) {
        std::cout << "ERROR, tree 2 has different operands than expected" << std::endl;
        isOK = false;
    }
    isOK = isOK && aT.isOK() && bT.isOK();

    if (!isOK)
        exit(-1);
}

void
testSwappingRightRightDepthN(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                             std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes,
                             int subDepth) {

    ExpressionTree expr{treeAsStringOne, 0, treeOneMaxDepth};
    ExpressionTree expr2{treeAsStringTwo, 0, treeTwoMaxDepth};
    expr.treeCrossover(expr2, subDepth, true, true, true);
    bool isOK = true;
    if (treeOneExpectedRes != expr.getEvaluatedResults()) {
        std::cout << "ERROR, tree 1 failed with sub" << std::endl;
        isOK = false;
    }
    if (treeTwoExpectedRes != expr2.getEvaluatedResults()) {
        std::cout << "ERROR, tree 2 failed with sub" << std::endl;
        isOK = false;
    }
    isOK = isOK && expr.isOK() && expr2.isOK();

    if (!isOK)
        exit(-1);
}

void
testSwappingRightRightDepthOne(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                               std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {
    testSwappingRightRightDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                 treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 1);
}

void
testSwappingRightRightDepthTwo(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                               std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {

    testSwappingRightRightDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                 treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 2);
}

void
testSwappingRightRightDepthThree(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                                 std::string treeAsStringTwo, int treeTwoMaxDepth,
                                 std::vector<bool> treeTwoExpectedRes) {

    testSwappingRightRightDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                 treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 3);
}

void testSwappingRightLeftDepthN(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                                 std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes,
                                 int subDepth) {

    ExpressionTree expr{treeAsStringOne, 0, treeOneMaxDepth};
    ExpressionTree expr2{treeAsStringTwo, 0, treeTwoMaxDepth};
    expr.treeCrossover(expr2, subDepth, true, true, false);

    bool isOK = true;

    if (treeOneExpectedRes != expr.getEvaluatedResults()) {
        std::cout << "ERROR, tree 1 failed with sub" << std::endl;
        isOK = false;
    }
    if (treeTwoExpectedRes != expr2.getEvaluatedResults()) {
        std::cout << "ERROR, tree 2 failed with sub" << std::endl;
        isOK = false;
    }
    isOK = isOK && expr.isOK() && expr2.isOK();

    if (!isOK)
        exit(-1);
}

void
testSwappingRightLeftDepthOne(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                              std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {
    testSwappingRightLeftDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 1);
}

void
testSwappingRightLeftDepthTwo(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                              std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {

    testSwappingRightLeftDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 2);
}

void testSwappingLeftLeftDepthN(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                                std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes,
                                int subDepth) {

    ExpressionTree expr{treeAsStringOne, 0, treeOneMaxDepth};
    ExpressionTree expr2{treeAsStringTwo, 0, treeTwoMaxDepth};
    expr.treeCrossover(expr2, subDepth, true, false, false);

    bool isOK = true;
    if (treeOneExpectedRes != expr.getEvaluatedResults()) {
        std::cout << "ERROR, tree 1 failed with sub" << std::endl;
        isOK = false;
    }
    if (treeTwoExpectedRes != expr2.getEvaluatedResults()) {
        std::cout << "ERROR, tree 2 failed with sub" << std::endl;
        isOK = false;
    }
    isOK = isOK && expr.isOK() && expr2.isOK();

    if (!isOK)
        exit(-1);
}

void
testSwappingLeftLeftDepthOne(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                             std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {
    testSwappingLeftLeftDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                               treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 1);
}

void
testSwappingLeftLeftDepthTwo(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                             std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {
    testSwappingLeftLeftDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                               treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 2);
}

void testSwappingLeftRightDepthN(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                                 std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes,
                                 int subDepth) {

    ExpressionTree expr{treeAsStringOne, 0, treeOneMaxDepth};
    ExpressionTree expr2{treeAsStringTwo, 0, treeTwoMaxDepth};

    expr.treeCrossover(expr2, subDepth, true, false, true);

    bool isOK = true;
    if (treeOneExpectedRes != expr.getEvaluatedResults()) {
        std::cout << "ERROR, tree 1 failed with sub" << std::endl;
        isOK = false;
    }
    if (treeTwoExpectedRes != expr2.getEvaluatedResults()) {
        std::cout << "ERROR, tree 2 failed with sub" << std::endl;
        isOK = false;
    }

    isOK = isOK && expr.isOK() && expr2.isOK();

    if (!isOK)
        exit(-1);
}

void
testSwappingLeftRightDepthOne(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                              std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {
    testSwappingLeftRightDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 1);
}

void
testSwappingLeftRightDepthTwo(std::string treeAsStringOne, int treeOneMaxDepth, std::vector<bool> treeOneExpectedRes,
                              std::string treeAsStringTwo, int treeTwoMaxDepth, std::vector<bool> treeTwoExpectedRes) {

    testSwappingLeftRightDepthN(treeAsStringOne, treeOneMaxDepth, treeOneExpectedRes,
                                treeAsStringTwo, treeTwoMaxDepth, treeTwoExpectedRes, 2);
}

void runExpressionTreeTests(bool isInQuietMode = false) {
//    testTree("NOT", 0, isInQuietMode);
//    testTree("!", 0, isInQuietMode);
//    testTree("OR", 0, isInQuietMode);
//    testTree("||", 0, isInQuietMode);
//    testTree("AND", 0, isInQuietMode);
//    testTree("&&", 0, isInQuietMode);

    testTree("A", 0, isInQuietMode, {1, 0});

    testTree("B NOT", 1, isInQuietMode, {0, 1});
    testTree("(B) NOT", 1, isInQuietMode, {0, 1});
    testTree("(a) NOT", 1, isInQuietMode, {0, 1});
    testTree("A && B", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("A || b", 1, isInQuietMode, {1, 1, 1, 0});
    testTree("A AND B", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("A OR B", 1, isInQuietMode, {1, 1, 1, 0});
    testTree("(A) AND (B)", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("(a) AND (b)", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("a AND (b)", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("(a) AND b", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("a AND b", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("(a) && (b)", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("a && (b)", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("(a) && b", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("a && b", 1, isInQuietMode, {1, 0, 0, 0});
    testTree("a XOR b", 1, isInQuietMode, {0, 1, 1, 0});
    testTree("A XOR B", 1, isInQuietMode, {0, 1, 1, 0});
    testTree("(b) OR (b)", 1, isInQuietMode, {1, 0});

    testTree("(A AND B) OR ((B) OR (A))", 2, isInQuietMode, {1, 1, 1, 0});
    testTree("(C AND A) AND ((C) XOR (D))", 2, isInQuietMode, {0, 1, 0, 0, 0, 0, 0, 0});
    testTree("(A AND B) OR (C XOR D)", 2, isInQuietMode, {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0});
    testTree("(C AND A) && (B || A)", 2, isInQuietMode, {1, 1, 0, 0, 0, 0, 0, 0});
    testTree("(A AND B) AND (A NOT)", 2, isInQuietMode, {0, 0, 0, 0});
    testTree("a && (b && c)", 2, isInQuietMode, {1, 0, 0, 0, 0, 0, 0, 0});
    testTree("a || (b || c)", 2, isInQuietMode, {1, 1, 1, 1, 1, 1, 1, 0});
    testTree("((b) NOT) OR ((a) AND (b))", 2, isInQuietMode, {1, 0, 1, 1});
    testTree("((b) NOT) OR ((b) OR (b))", 2, isInQuietMode, {1, 1});
    testTree("((a) OR (b)) NOT", 2, isInQuietMode, {0, 0, 0, 1});

    testTree("(a) && ((b) && ((c) || (d)))", 3, isInQuietMode, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    testTree("(a) && ((A || B) && (!C))", 3, isInQuietMode, {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    testTree("(a) && ((b && c) || ((A || B) && (!C)))", 4, isInQuietMode,
             {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    testTree(
            "(((((b) AND (b)) NOT) OR (((a) NOT) OR ((b) OR (a)))) NOT) OR (((((b) OR (b)) AND ((b) AND (b))) NOT) NOT)",
            5, isInQuietMode, {1, 1, 0, 0});
    testTree("a && (b && (c && (d && (e && (!f)))))", 6, isInQuietMode,
             {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    // Simple XOR equivalent
    testTree("(A && (!B)) OR ((!A) AND (B))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(A && (!B)) OR ((!A) AND B)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("((A) && (!B)) OR ((!A) && B)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("((A) AND (!B)) || ((!A) && B)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(A OR B) AND ((!A) OR (!B))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(A || B) && ((!A) OR (!B))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(A OR B) AND ((A AND B) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(A OR B) AND ((A AND B) !)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((a) OR (b)) OR ((a) AND (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((b) AND (b)) OR ((a) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) NOT) AND (((a) OR (b)) OR ((a) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) NOT) AND (((a) AND (b)) OR ((a) OR (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) OR (b)) OR ((a) AND (b))) AND (((a) AND (b)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) OR (b)) OR ((b) AND (b))) AND (((a) AND (b)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((b) OR (a)) OR ((b) AND (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (a)) OR ((a) OR (a))) AND (((a) AND (b)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) NOT) AND (((b) OR (a)) OR ((a) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) NOT) AND ((a) OR (b))) OR (((a) OR (b)) AND ((b) NOT))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((a) AND (b)) OR ((a) OR (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) NOT) AND (((b) AND (b)) OR ((a) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) OR ((b) OR (a))) AND (((a) AND (b)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((b) AND (b)) OR ((a) OR (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (b)) AND ((a) NOT)) OR (((b) NOT) AND ((a) OR (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) AND (b)) NOT) AND (((b) OR (a)) OR ((b) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) NOT) OR ((b) NOT)) AND (((b) OR (a)) OR ((b) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) NOT) AND ((b) OR (a))) OR (((a) OR (a)) AND ((b) NOT))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) NOT) OR ((b) NOT)) AND (((a) OR (a)) OR ((b) OR (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) NOT) OR ((a) NOT)) AND (((a) AND (a)) OR ((b) OR (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (a)) AND ((a) NOT)) OR (((b) NOT) AND ((a) AND (a)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (a)) OR ((b) AND (a))) AND (((b) AND (a)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (a)) OR ((b) AND (b))) AND (((b) AND (a)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (a)) NOT) AND (((a) OR (b)) OR ((a) AND (b)))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) OR (a)) AND ((b) OR (a))) AND (((b) AND (a)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((a) NOT) AND ((b) OR (b))) OR (((b) OR (a)) AND ((b) NOT))", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) AND (b)) OR ((b) OR (a))) AND (((a) AND (b)) NOT)", 3, isInQuietMode, {0, 1, 1, 0});
    testTree("(((b) NOT) AND ((b) OR (a))) OR (((a) NOT) AND ((b) AND (b)))", 3, isInQuietMode, {0, 1, 1, 0});

    testTree(
            "(((((b) OR (a)) NOT) OR (((a) AND (a)) AND ((b) AND (b)))) OR ((((b) OR (a)) AND ((a) OR (b))) AND (((a) AND (b)) AND ((a) NOT)))) NOT",
            5, isInQuietMode, {0, 1, 1, 0});
    testTree(
            "(((((b) NOT) AND ((b) OR (b))) OR (((a) OR (b)) NOT)) NOT) AND (((((b) AND (a)) NOT) AND (((b) OR (a)) OR ((b) NOT))) OR ((((a) OR (a)) NOT) AND (((b) NOT) OR ((a) AND (a)))))",
            5, isInQuietMode, {0, 1, 1, 0});

    testTree("((((C) NOT) OR ((B) AND (C))) NOT) OR ((((B) OR (A)) NOT) OR (((C) NOT) NOT))", 4, isInQuietMode,
             {1, 1, 1, 1, 0, 0, 0, 1});
    testTree(
            "((((B) OR (C)) AND ((B) NOT)) OR (((B) AND (A)) NOT)) AND ((((C) AND (A)) OR ((C) OR (B))) AND (((B) AND (A)) OR ((A) AND (C))))",
            4, isInQuietMode, {0, 0, 0, 0, 1, 0, 0, 0});

    testTree("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, isInQuietMode, {1, 1, 1, 1, 1, 0, 0, 0});
    testTree("((B) NOT) NOT", 2, isInQuietMode, {1, 0});

    testTree("((((C) NOT) OR ((B) AND (C))) NOT) AND ((A) NOT)", 4, isInQuietMode, {0, 0, 0, 1, 0, 0, 0, 0});
    testTree("(((C) NOT) OR ((B AND C) NOT)) AND ((A) NOT)", 4, isInQuietMode, {0, 0, 0, 1, 0, 1, 0, 1});
    testTree("(((C) NOT) OR ((B AND C) NOT)) OR (((B OR A) NOT) OR (((C) NOT) NOT))", 4, isInQuietMode,
             {1, 1, 1, 1, 1, 1, 1, 1});
}

void runAllTests(bool quietMode = false) {
    runExpressionTreeTests(quietMode);
    testSwappingTrees("((A) && (!B)) OR ((!A) && B)", 3, {0, 0, 0, 0},
                      "((A) || (!B)) AND ((!A) && A)", 3, {1, 1, 0, 1},
                      0);
    // Substitute just function of the root
    testSwawppingRootFuncForTreeInDepthOne("C AND A",
                                           "C || A",
                                           {1, 1, 1, 0},
                                           {1, 0, 0, 0});
    testSwappingTreesTerminals("C", "B", {'C'}, {'B'});
    testSwappingRightRightDepthOne("(C AND A) && (B)", 2, {0, 1, 0, 0, 0, 0, 0, 0},
                                   "(A AND B) OR ((B) NOT)", 2, {1, 0, 1, 0});
    testSwappingRightRightDepthTwo("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, {1, 1, 1, 1, 0, 0, 1, 0},
                                   "((B) NOT) NOT", 2, {0, 0});
    testSwappingRightRightDepthThree("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, {1, 1, 1, 1, 1, 0, 0, 0},
                                     "(((B) NOT) NOT) AND ((A OR B) OR (B XOR C))", 3, {1, 1, 0, 0});
    testSwappingRightLeftDepthOne("(C AND A) && (B || A)", 4, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  "(D AND B) OR (C XOR B)", 3, {1, 1, 1, 1, 1, 1, 1, 0});
    testSwappingRightLeftDepthTwo("(C AND A) && (B || A)", 4, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  "(D AND B) OR (C XOR B)", 3, {1, 1, 1, 0, 0, 1, 1, 0});
    testSwappingLeftLeftDepthOne("(((C) NOT) OR ((B AND C) NOT)) OR (((B OR A) NOT) OR (((C) NOT) NOT))", 4,
                                 {1, 1, 1, 1, 1, 0, 1, 1},
                                 "(A) AND ((A) NOT)", 2, {0, 0, 0, 1, 0, 1, 0, 1});
    testSwappingLeftLeftDepthTwo("(((C) NOT) OR ((B AND C) NOT)) OR (((B OR A) NOT) OR (((C) NOT) NOT))", 4,
                                 {1, 1, 1, 1, 1, 1, 1, 1},
                                 "(A) AND ((A) NOT)", 2, {0, 0, 0, 1});
    testSwappingRightRightDepthThree("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, {1, 1, 1, 1, 1, 0, 0, 0},
                                     "(((B) NOT) NOT) AND ((A OR B) OR (B XOR C))", 3, {1, 1, 0, 0});
    testSwappingLeftRightDepthOne("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, {1, 1, 0, 0},
                                  "((B) NOT) NOT", 2, {1, 0});
    testSwappingLeftRightDepthTwo("(C AND C) OR ((A AND B) XOR (A AND ((A) NOT)))", 4, {1, 1, 1, 0, 0, 0, 0, 0},
                                  "(D AND B) OR (C XOR B)", 2, {1, 1, 0, 0, 0, 0, 0, 0});
    testRightRightDepth1();
//    std::string one = "((b) NOT) AND (b)";
//    std::string two = "((b) NOT) AND (b)";
//    ExpressionTree exprOne{one, 0, 2};
//    ExpressionTree exprTwo{two, 0, 2};
//    std::vector<bool> oneExpectedRes = {1, 0};
//    std::vector<bool> twoExpectedRes = {1, 0};
//    std::vector<char> oneExpectedOperandsTerminals = {'b'};
//    std::vector<char> twoExpectedOperandsTerminals = {'b'};
//    std::vector<ExpressionTreeFunctions> oneFuncs = {};
//    std::vector<ExpressionTreeFunctions> twoFuncs = {};
//    exprOne.treeCrossover(exprTwo, 1);
//
//    std::vector<bool> oneActualRes = exprOne.getEvaluatedResults();
//    std::vector<bool> twoActualRes = exprTwo.getEvaluatedResults();
//    std::vector<char> oneActualTerminals = exprOne.getAllOperands();
//    std::vector<char> twoActualTerminals = exprTwo.getAllOperands();
//    std::vector<ExpressionTreeFunctions> oneActualFuncs = exprOne.getAllFunctions();
//    std::vector<ExpressionTreeFunctions> twoActualFuncs = exprTwo.getAllFunctions();
//    if (oneExpectedRes != oneActualRes)
//        std::cout << "One: results different" << std::endl;
//    if (twoExpectedRes != twoActualRes)
//        std::cout << "Two: results different" << std::endl;
//    if (oneExpectedOperandsTerminals != oneActualTerminals)
//        std::cout << "One: operands different" << std::endl;
//    if (twoExpectedOperandsTerminals != twoActualTerminals)
//        std::cout << "Two: operands different" << std::endl;
//    if (oneFuncs != oneActualFuncs)
//        std::cout << "One: funcs different" << std::endl;
//    if (twoFuncs != twoActualFuncs)
//        std::cout << "Two: funcs different" << std::endl;

    std::string e = "(b) OR";
    ExpressionTree ee{e, 0,1};
    if (ee.isOK()){
        std::cout << "Expression is wrong" << std::endl;
        exit(-1);
    }
//    "(a) OR ((a) NOT)"
//    "(b) NOT"
//    firstExpr.treeCrossover(secondExpr, 0));
}

void testRightRightDepth1() {
    std::string one = "C AND A";
    std::string two = "(B) NOT";
    ExpressionTree exprOne{one, 0, 1};
    ExpressionTree exprTwo{two, 0, 1};
    std::vector<bool> oneExpectedRes = {0, 1, 0, 0};
    std::vector<bool> twoExpectedRes = {1, 0};
    std::vector<char> oneExpectedOperandsTerminals = {'C', 'B'};
    std::vector<char> twoExpectedOperandsTerminals = {'A'};
    std::vector<ExpressionTreeFunctions> oneFuncs = {AND, NOT};
    std::vector<ExpressionTreeFunctions> twoFuncs = {};
    exprOne.treeCrossover(exprTwo, 1, true, true, true);

    std::vector<bool> oneActualRes = exprOne.getEvaluatedResults();
    std::vector<bool> twoActualRes = exprTwo.getEvaluatedResults();
    std::vector<char> oneActualTerminals = exprOne.getAllOperands();
    std::vector<char> twoActualTerminals = exprTwo.getAllOperands();
    std::vector<ExpressionTreeFunctions> oneActualFuncs = exprOne.getAllFunctions();
    std::vector<ExpressionTreeFunctions> twoActualFuncs = exprTwo.getAllFunctions();
    if (oneExpectedRes != oneActualRes)
        std::cout << "One: results different" << std::endl;
    if (twoExpectedRes != twoActualRes)
        std::cout << "Two: results different" << std::endl;
    if (oneExpectedOperandsTerminals != oneActualTerminals)
        std::cout << "One: operands different" << std::endl;
    if (twoExpectedOperandsTerminals != twoActualTerminals)
        std::cout << "Two: operands different" << std::endl;
    if (oneFuncs != oneActualFuncs)
        std::cout << "One: funcs different" << std::endl;
    if (twoFuncs != twoActualFuncs)
        std::cout << "Two: funcs different" << std::endl;
    if (!exprOne.isOK())
        std::cout << "One: tree is not OK" << std::endl;
    if (!exprTwo.isOK())
        std::cout << "Two: tree is not OK" << std::endl;

}

#endif //AILABGENETICALGORITHM_OPTIMALXORAUTOTESTS_H
