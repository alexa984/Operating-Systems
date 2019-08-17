
    #!/bin/bash
    # Print message, passed as parameter to the script in center of terminal
    cols=$( tput cols )
    rows=$( tput lines )
    message=$@
    input_length=${#message}
    half_input_length=$(( $input_length / 2 ))
    middle_row=$(( $rows / 2 ))
    middle_col=$(( ($cols / 2) - $half_input_length ))
    tput clear
    tput cup $middle_row $middle_col
    tput bold
    echo $@
    tput sgr0
    tput cup $( tput lines ) 0

