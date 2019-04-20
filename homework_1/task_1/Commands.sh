data_path='./data/data.dat'
num_lines='0'
num_contain_dolor_or_dalor='0'
num_words='0'
num_line_start_with_mol='0'


num_lines=$(wc -l $data_path | awk '{print $1}')
num_contain_dolor_or_dalor=$(grep 'dolor\|dalor' $data_path | wc -l)
num_words=$(wc -w $data_path | awk '{print $1}')
num_line_start_with_mol=$(grep ^mol $data_path | wc -l)


echo $'the total line number is: ' $num_lines
echo $'lines of those contain 'dolor' or 'dalor' is: ' $num_contain_dolor_or_dalor
echo $'the total word number is: ' $num_words
echo $'the number of lines starting with 'mol' is: ' $num_line_start_with_mol



