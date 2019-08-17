#!/bin/bash
shell_variable_1=10
shell_variable_2=20
shell_variable_3=30

run_awk() {
        awk -v shell_variable_1="$shell_variable_1" \
            -v shell_variable_2="$shell_variable_2" \
            -v shell_variable_3="$shell_variable_3" '
        function A(X) { return X+1 }
        { a=A(shell_variable_1)
          b=A(shell_variable_2)
          c=A(shell_variable_3) }
        END {
          print "shell_variable_1=" a
          print "shell_variable_2=" b
          print "shell_variable_3=" c
        }' <<<""
}

while IFS="=" read -r key value; do
        printf -v "$key" '%s' "$value"
done < <(run_awk)

for var in shell_variable_{1,2,3}; do
  printf 'New value for %s is %s\n' "$var" "${!var}"
done
