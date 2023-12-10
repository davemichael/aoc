sed 's/[A-Za-z]//g' $1 |  # Get rid of alphabet characters
    sed -E 's/^(.).*(.)$/\1\2/' |  # Get rid of middle characters
    sed -E 's/^(.)$/\1\1/' |  # Any strings with 1 digit, duplicate that digit
    paste -sd+ |  # turn into a single line summation
    bc  # calculate

