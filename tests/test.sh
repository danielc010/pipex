#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Disable core dumps for this script
ulimit -c 0

test_count=0
pass_count=0

echo "========== PIPEX TESTS =========="

# Test 1: Basic cat | wc
echo -e "\n${BLUE}Test 1: cat | wc -l${NC}"
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
echo -e "\n${BLUE}Test 2: grep | wc -l${NC}"
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
echo -e "\n${BLUE}Test 3: Invalid first command${NC}"
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
echo -e "\n${BLUE}Test 4: Invalid second command${NC}"
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
echo -e "\n${BLUE}Test 5: Both commands invalid${NC}"
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
echo -e "\n${BLUE}Test 6: File doesn't exist${NC}"
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
echo -e "\n${BLUE}Test 7: Empty file${NC}"
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

echo -e "\n${YELLOW}========== BONUS: MULTIPLE PIPES ==========${NC}"

# Test 8: Three commands
echo -e "\n${BLUE}Test 8: Three commands (cat | grep | wc)${NC}"
echo -e "hello world\ngoodbye world\nhello again\ntest line" > test_in.txt
./pipex test_in.txt "cat" "grep hello" "wc -l" test_out.txt 2>/dev/null
expected=$(< test_in.txt cat | grep hello | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 9: Four commands
echo -e "\n${BLUE}Test 9: Four commands (cat | sort | uniq | wc)${NC}"
echo -e "apple\nbanana\napple\ncherry\nbanana" > test_in.txt
./pipex test_in.txt "cat" "sort" "uniq" "wc -l" test_out.txt 2>/dev/null
expected=$(< test_in.txt cat | sort | uniq | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 10: Five commands
echo -e "\n${BLUE}Test 10: Five commands (cat | grep | sort | uniq | wc)${NC}"
echo -e "test1\nhello\ntest2\nhello\nworld\ntest3" > test_in.txt
./pipex test_in.txt "cat" "grep test" "sort" "uniq" "wc -l" test_out.txt 2>/dev/null
expected=$(< test_in.txt cat | grep test | sort | uniq | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 11: Multiple pipes with tr
echo -e "\n${BLUE}Test 11: Multiple pipes with tr (cat | tr | wc)${NC}"
echo -e "HELLO WORLD" > test_in.txt
./pipex test_in.txt "cat" "tr 'A-Z' 'a-z'" "wc -c" test_out.txt 2>/dev/null
expected=$(< test_in.txt cat | tr 'A-Z' 'a-z' | wc -c | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

echo -e "\n${YELLOW}========== BONUS: HERE_DOC ==========${NC}"

# Test 12: Basic here_doc with EOF
echo -e "\n${BLUE}Test 12: Basic here_doc (EOF limiter)${NC}"
rm -f test_heredoc.txt
echo -e "line1\nline2\nline3\nEOF" | ./pipex here_doc EOF "cat" "wc -l" test_heredoc.txt 2>/dev/null
expected="3"
actual=$(cat test_heredoc.txt 2>/dev/null | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 13: Here_doc with grep
echo -e "\n${BLUE}Test 13: Here_doc with grep${NC}"
rm -f test_heredoc.txt
echo -e "hello world\ngoodbye\nhello again\nSTOP" | ./pipex here_doc STOP "grep hello" "wc -l" test_heredoc.txt 2>/dev/null
expected="2"
actual=$(cat test_heredoc.txt 2>/dev/null | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 14: Here_doc with different limiter
echo -e "\n${BLUE}Test 14: Here_doc with custom limiter (END)${NC}"
rm -f test_heredoc.txt
echo -e "data1\ndata2\ndata3\ndata4\nEND" | ./pipex here_doc END "cat" "wc -l" test_heredoc.txt 2>/dev/null
expected="4"
actual=$(cat test_heredoc.txt 2>/dev/null | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 15: Here_doc APPEND mode (critical test!)
echo -e "\n${BLUE}Test 15: Here_doc APPEND mode (run twice)${NC}"
rm -f test_heredoc.txt
echo -e "first\nEOF" | ./pipex here_doc EOF "cat" "cat" test_heredoc.txt 2>/dev/null
echo -e "second\nEOF" | ./pipex here_doc EOF "cat" "cat" test_heredoc.txt 2>/dev/null
actual=$(cat test_heredoc.txt 2>/dev/null)
test_count=$((test_count + 1))
if echo "$actual" | grep -q "first" && echo "$actual" | grep -q "second"; then
    echo -e "${GREEN}✓ PASS${NC} (correctly appended both runs)"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (should contain both 'first' and 'second')"
    echo "Got: $actual"
fi

# Test 16: Here_doc with cat and sort
echo -e "\n${BLUE}Test 16: Here_doc with sort${NC}"
rm -f test_heredoc.txt
echo -e "zebra\napple\nmango\nEOF" | ./pipex here_doc EOF "cat" "sort" test_heredoc.txt 2>/dev/null
expected=$'apple\nmango\nzebra'
actual=$(cat test_heredoc.txt 2>/dev/null)
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC}"
    echo "Expected: $expected"
    echo "Got: $actual"
fi

# Test 17: Here_doc with empty input
echo -e "\n${BLUE}Test 17: Here_doc with empty input${NC}"
rm -f test_heredoc.txt
echo "EOF" | ./pipex here_doc EOF "cat" "wc -l" test_heredoc.txt 2>/dev/null
expected="0"
actual=$(cat test_heredoc.txt 2>/dev/null | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Test 18: Here_doc limiter in middle of text (should not stop)
echo -e "\n${BLUE}Test 18: Here_doc limiter as part of line (should not stop)${NC}"
rm -f test_heredoc.txt
echo -e "this is EOF in middle\nactual line\nEOF" | ./pipex here_doc EOF "cat" "wc -l" test_heredoc.txt 2>/dev/null
expected="2"
actual=$(cat test_heredoc.txt 2>/dev/null | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

echo -e "\n${YELLOW}========== BONUS: COMBINED ==========${NC}"

# Test 19: Multiple pipes work with regular files (not just here_doc)
echo -e "\n${BLUE}Test 19: Verify multiple pipes still work with files${NC}"
echo -e "1\n2\n3\n4\n5" > test_in.txt
./pipex test_in.txt "cat" "grep 1" "wc -l" test_out.txt 2>/dev/null
expected=$(< test_in.txt cat | grep 1 | wc -l | tr -d ' ')
actual=$(cat test_out.txt | tr -d ' ')
test_count=$((test_count + 1))
if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}✓ PASS${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAIL${NC} (expected: $expected, got: $actual)"
fi

# Cleanup
rm -f test_in.txt test_out.txt test_heredoc.txt empty_test.txt

echo -e "\n${YELLOW}========== RESULTS ==========${NC}"
echo -e "Passed: ${GREEN}$pass_count${NC}/${test_count}"

if [ $pass_count -eq $test_count ]; then
    echo -e "${GREEN}All tests passed! 🎉${NC}"
    exit 0
else
    failed=$((test_count - pass_count))
    echo -e "${RED}$failed test(s) failed${NC}"
    exit 1
fi
