#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

test_count=0
pass_count=0

echo "========== PIPEX TESTS =========="

# Test 1: Basic cat | wc
echo -e "\nTest 1: cat | wc -l"
echo -e "line1\nline2\nline3" > test_in.txt
./pipex test_in.txt "cat" "wc -l" test_out.txt
expected=$(< test_in.txt cat | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 2: grep | wc
echo -e "\nTest 2: grep | wc -l"
./pipex test_in.txt "grep in" "wc -l" test_out.txt
expected=$(< test_in.txt grep in | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 3: Invalid first command
echo -e "\nTest 3: Invalid first command"
./pipex test_in.txt "notacommand" "wc" test_out.txt 2>/dev/null
EXIT_CODE=$?
test_count=$((test_count + 1))
if [ $EXIT_CODE -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (correctly failed with exit code $EXIT_CODE)"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (should have failed, got exit code $EXIT_CODE)"
fi

# Test 4: Invalid second command
echo -e "\nTest 4: Invalid second command"
./pipex test_in.txt "cat" "notacommand" test_out.txt 2>/dev/null
EXIT_CODE=$?
test_count=$((test_count + 1))
if [ $EXIT_CODE -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (correctly failed with exit code $EXIT_CODE)"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (should have failed, got exit code $EXIT_CODE)"
fi

# Test 5: Both commands invalid
echo -e "\nTest 5: Both commands invalid"
./pipex test_in.txt "fake1" "fake2" test_out.txt 2>/dev/null
EXIT_CODE=$?
test_count=$((test_count + 1))
if [ $EXIT_CODE -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (correctly failed with exit code $EXIT_CODE)"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (should have failed, got exit code $EXIT_CODE)"
fi

# Test 6: File doesn't exist
echo -e "\nTest 6: File doesn't exist"
./pipex ghost.txt "cat" "wc" test_out.txt 2>/dev/null
EXIT_CODE=$?
test_count=$((test_count + 1))
if [ $EXIT_CODE -ne 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (correctly failed with exit code $EXIT_CODE)"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (should have failed, got exit code $EXIT_CODE)"
fi

# Test 7: Empty file
echo -e "\nTest 7: Empty file"
touch empty_test.txt
./pipex empty_test.txt "cat" "wc -l" test_out.txt 2>/dev/null
EXIT_CODE=$?
expected="0"
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ $EXIT_CODE -eq 0 ] && [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected lines, got: $actual, exit: $EXIT_CODE)"
fi
rm -f empty_test.txt

# Cleanup
rm -f test_in.txt test_out.txt

echo -e "\n========== RESULTS =========="
echo "Passed: $pass_count/$test_count"
