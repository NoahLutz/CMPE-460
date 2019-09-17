% LaTex class file for generating KGCOE reports
% https://kgcoe-git.rit.edu/jgm6496/KGCOEReport_template

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{KGCOEReport}[2016/05/25 Example LaTeX class]

%%%%%%% Base class
\LoadClass[12pt]{article}

%%%%%%% Required packages
\RequirePackage{multicol} %Make columns
\RequirePackage[margin=1in]{geometry} %Change margins
\RequirePackage[most]{tcolorbox}  % For the "RIT" box on EEEE cover

%%%%% Extra required packages
\RequirePackage{graphicx}	%provides some extra features for including graphics. 
\RequirePackage{float}	%Provides the [H] for hard setting things. It means "Put this exactly here
\RequirePackage[outdir=./]{epstopdf}	%Used to include .eps vector images
\RequirePackage{caption} %So you can caption things bettr
\RequirePackage{siunitx} % Formats units and values
\RequirePackage{pgfplotstable} % Generates table from .csv
\RequirePackage{tocloft} % Adds the ability to format the Table of contensts
\RequirePackage{csvsimple}

\setlength{\parindent}{0pt} % Don't indent paragraphs

%%%%%%% Internal functions and environments
% Used to make sure the TA listing is even
\newenvironment{_TAalignment}{%
\def\\{\newline\leavevmode\phantom{TAs:}}
}

%%%%%%% External functions and environments

%%%%%%% Write a CE report
\DeclareOption{CMPE}{
	\newcommand{\KGCOEDocType}{CMPE}

	\renewcommand{\maketitle}{%
	\vspace*{2.5cm}

		\begin{center}
			\large
			\textbf{\classCode \ Laboratory Exercise \exerciseNumber}

			\bigskip

			\textbf{\exerciseDescription}
			\normalsize
		\end{center}

		\vspace*{8cm}

		\begin{multicols}{2}
			\phantom{LaTeX doesn't like empty columns} % Phantom will take up that much space, but not actually appear
			\columnbreak{} % Starts the second column
			\begin{flushleft} % Make sure LaTeX does not try to justify these lines
				\name\\
				Performed: \dateDone\\
				Submitted: \dateSubmitted\\
				\vspace*{\baselineskip} % Adds one line of spacing on this line, like the template
				Lab Section: \LabSectionNum\\
				Instructor: \LabInstructor\\
				TAs:\begin{_TAalignment}\TAs  % There can't be a space between the \TAs and the enviroment declaration
				\end{_TAalignment}
				\vspace*{\baselineskip}
				Lecture Section: \LectureSectionNum\\
				Professor: \LectureInstructor\\
			\end{flushleft}
		\end{multicols}

		\newpage
	}
}
%%%%%%% Write a EE report
\DeclareOption{EEEE}{
	\newcommand{\KGCOEDocType}{EEEE}

	\renewcommand{\maketitle}{%

		\begin{flushright}\begin{tcolorbox}[colback=black,coltext=white,halign=center,boxrule=0pt,
			sharp corners, width=0.5\textwidth, fontupper={\Large \bfseries}]
			Rochester Institute of \\ Technology
		\end{tcolorbox}\end{flushright}

		\huge
		\textbf{\classCode \ - \className \ Technical Memo}\\
		\normalsize

		\noindent
		\begin{tabular}{ll}
		\textbf{From:} &\name\\

		% Optional parameter of partner
		\ifdefined\partnerName
			\textbf{Partner:} &\partnerName\\
			\\
		\fi

		\textbf{To:} &\TAs \ | Section \LabSectionNum\\
		\textbf{Date:} &Performed: \dateDone; Due: \dateSubmitted\\
		\textbf{Subject:} &Lab \exerciseNumber: \exerciseDescription
		\end{tabular}

		\noindent
		\rule{\textwidth}{.1pt}
	}
}
% Pass any other options to
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions

%%%%%%% Check to see if we were given a correct department code
\@ifundefined{KGCOEDocType}{\ClassError{KGCOEReport}{Unrecognized Department Code}{Available department codes are CMPE, EEEE}}{}


%%%%%%% Extra helper funcions and options


%To get numbers into Engineering notation, use \num{thhe number here} 
\sisetup{exponent-product = \times ,round-mode = figures,%
	  round-precision = 5, scientific-notation = engineering}

%These are the caption declarations for equations and tables. 
\DeclareCaptionType{equationCaption}[][List of equations]
\DeclareCaptionType{tableCaption}[][List of Tables]
\captionsetup[equationCaption]{name=Equation}%{labelformat=Equation}
\captionsetup[tableCaption]{name=Table}%{labelformat=Equation}

%Pretty print the ohm symbol with \ohm
\newcommand{\ohm}{$\Omega$}


%This pretty prints an equation. 
%1st arg: The label to be used for reference 
%2nd arg: The equation. Use Math Mode. 
%3rd arg: The caption text. 
% \eq{ReferenceName}{y=mx+b}{CaptionTitle}
\newcommand{\eq}[3]{
	\begin{equationCaption}[H]
		\begin{equation}
			#2
			\label{#1}
		\end{equation}
		\caption{#3}
	\end{equationCaption}}
\newcommand{\multieq}[4]{
	\begin{equationCaption}[H]
		\begin{align}
			\label{#1}
			#3
			\label{#2}
		\end{align}
		\caption{#4}
	\end{equationCaption}}
%Adds an image, captions and labels. 
%1: Optional arguments to \includegraphics. Use to set image params. 
%2: The label for referential purposes. 
%3: The filename
%4: The caption
% \nimg{ReferenceName}{Filename}{CaptionTitle}
\newcommand{\nimg}[4][width=\textwidth]{
	\begin{figure}[H]
		\centering
		\includegraphics[ #1]{#3}
		\caption{#4}
		\label{#2}
	\end{figure}
}
% This is so that there is lines between the items in the table. 
\makeatletter
\csvset{
	my hack/.style={
		%early before header=\\\hline,
		late after line=\\\hline,
		late after last line=\csv@tablefoot\end{tabular}\csv@posttable},
}
\makeatother
\newcommand{\ntab}[3]{
	\begin{table}[H]
		\centering
		\csvautotabular[my hack]{#2}

		\caption{#3}
		\label{#1}
	\end{table}
}
%This adds a large block of text to the document.                                                                                                                                               
%1st arg: The label to be used for reference                                       
%2nd arg: The filename                                                             
%3rd arg: The caption text.                                                        
\newcommand{\blocktext}[3]{                                                        
    \newpage                                                                   
	\lstinputlisting[basicstyle=\tiny, stringstyle=\ttfamily, numbers=left, breaklines, caption={#3}, label={#1}]{#2}
    %Add a new page at the end to add some separation.                 
\centering{End Listing \ref{#1}}                                                
                \newpage                                                        
}                                                                               
            





