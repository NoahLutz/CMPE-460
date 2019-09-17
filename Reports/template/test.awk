BEGIN { FS="," 
	}
{
if (NR == 1){	
	print $0
	print NF
	split(FILENAME, file,".")
	outputFile = file[1] ".tex"
	printf "\\begin\{table\}\[H\]\n" > outputFile
	printf " \\centering\n" > outputFile
	print ($NF-1)
	printf " \\begin\{tabular\}\[H\]\{|" > outputFile
	for(c=0;c<NF;c++) printf " l |" > outputFile
	printf "\}\n" > outputFile
	print "\\hline\n" > outputFile
	caption=$0
	FPAT = "([^,]+)|(\"[^\"]+\")"
}
else {
	  for (i=1; i<NF; i++){
		  
		  gsub("\"","",$(i))
		  gsub("\"","",$(i))
		  gsub("\"","",$(i))
		  printf "%s & ", $(i) > outputFile
	  }
		  gsub("\"","",$(NF))
	printf " %s \\\\ \\hline \n", $(NF) > outputFile
  }
  }
END {
	printf "\\end\{tabular\}\n" > outputFile
	gsub(",+$","", caption)
	printf "\\caption\{%s\}\n", caption  > outputFile
	#split(FILENAME, file,".")
	printf "\\label\{tab:%s\}\n", file[1] > outputFile
	printf "\\end\{table\}\n" > outputFile
}
