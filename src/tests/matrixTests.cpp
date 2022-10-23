#include "gtest/gtest.h"
#include "../matrix.h"

namespace{
    TEST(IOTest,FileDoesntExist){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/fsdfewgxgf.txt"));
    }
    TEST(MatrixCorrectTest,defaultMatrix){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
    }
    TEST(MatrixCorrectTest,emptyStringMatrix){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/emptyString.txt");
    }
    TEST(MatrixCorrectTest,manySpacesMatrix){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/manySpaces.txt");
    }
    TEST(MatrixCorrectTest,comentsAfterNumbers){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/comentsAfterNumbers.txt");
    }
    TEST(MatrixCorrectTest,comentsInLines){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/comentsInLines.txt");
    }
    TEST(MatrixCorrectTest,allInOne){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/allInOne.txt");
    }
    TEST(MatrixCorrectTest,zerosBeforeNumbers){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/zerosBeforeNumbers.txt");
    }
    TEST(MatrixCorrectTest,bigNums){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/bigNums.txt");
    }
    TEST(MatrixInCorrectTest,badCommentInLine){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/badCommentInLine.txt"));
    }
    TEST(MatrixInCorrectTest,badCommentAfterNumbers){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/badCommentAfterNumbers.txt"));
    }
    TEST(MatrixInCorrectTest,sumbolsAfterComment){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/symbolsAfterComment.txt"));
    }
    TEST(MatrixInCorrectTest,unclosedComment){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/unclosedComment.txt"));
    }
    TEST(MatrixInCorrectTest,unmarkedComment){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/unmarkedComment.txt"));
    }
    TEST(MatrixInCorrectTest,unequalValuesInLine){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/unequalValuesInLine.txt"));
    }
    TEST(MatrixInCorrectTest,spacesBetweenLitters){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/spacesBetweenLitters.txt"));
    }
    TEST(MatrixInCorrectTest,unequalLines){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/unequalLines.txt"));
    }
    TEST(MatrixInCorrectTest,badInequality1){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/badInequality1.txt"));
    }
    TEST(MatrixInCorrectTest,badInequality2){
        DilemmaMatrix m;
        EXPECT_ANY_THROW(m.fillMatrixFromFile("../src/tests/matrixes/badInequality2.txt"));
    }

    TEST(MatrixGetterTest,getterCorrectWork){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_TRUE(m.getValue("CCC",'C') == 7);
        EXPECT_TRUE(m.getValue("CCD",'C') == 3);
        EXPECT_TRUE(m.getValue("CCD",'D') == 9);
        EXPECT_TRUE(m.getValue("CDD",'C') == 0);
        EXPECT_TRUE(m.getValue("CDD",'D') == 5);
        EXPECT_TRUE(m.getValue("DDD",'D') == 1);
    }
    TEST(MatrixGetterTest,valueOfCinDDD){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("DDD",'C'));
    }
    TEST(MatrixGetterTest,valueOfDinCCC){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("CCC",'D'));
    }
    TEST(MatrixGetterTest,incorrectCode1){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("AAA",'D'));
    }
    TEST(MatrixGetterTest,hashCollision){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("Q<;",'D'));
    }
    TEST(MatrixGetterTest,incorrectType){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("CCC",'a'));
    }
    TEST(MatrixGetterTest,incorrectCase){
        DilemmaMatrix m;
        m.fillMatrixFromFile("../src/tests/matrixes/default.txt");
        EXPECT_ANY_THROW(m.getValue("ccc",'C'));
    }
}