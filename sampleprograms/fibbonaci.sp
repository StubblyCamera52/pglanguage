" this code computes a fibbonaci number (n) "

" the interpreter automatically creates a variable named {arg} which is the single input into the program. "
" here we are settng it to +1 because the program computes fibbonaci starting from 0, 1 and i want it to start from 1, 1 "
arg arg 1 + =;

var i;
" the equal operator pops 2 values off the stack and assigns the top value to the second one "
" so this line 1st - pushes {i} onto the stack "
" 2nd - pushes {2} onto the stack (stack is now TOP->2,i) "
" 3rd - pops both values off and sets {i} to {2} "
i 2 =;

var result;
result 0 =;


" blocks are pushed onto the stack and the code inside is not executed until if or while is called "
{
" when printenv [variable] is called it prints with the format variable: value "
" so we can use it to basically print string literals "
printenv n_must_be_greater_than_or_equal_to_zero;
" this is another command, it ends the current program early "
end;
}
" {<} operator pops two values and checks if top value {<} next value "
" if true it pushes {1} if false it pushes {0} "
0 arg <;
" {if} pops two values off of the stack and runs the code in the second value if the first is 1 (true)"
" so currently {1} is on the top of the stack "
" so {if} pops {1} and the previously pushed block, and since the comparison is true, it executes the block. "
if;

{
result 0 =;
printenv result;
end;
}
1 arg ==;
if;

var a;
var b;
a 0 =;
b 1 =;
var intermediate;
intermediate 0 =;

{
intermediate a =;
a b =;
b intermediate b + =;
i 1 i + =;
}
{ i arg >; }
while;

result b =;

" prints the result to the console "
printenv result;
" not technically needed since we are already at the end "
end;
