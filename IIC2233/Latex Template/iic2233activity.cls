\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{iic2233activity}[2018/08/01 IIC2233 activity class]
\LoadClass[11pt]{extarticle}

\RequirePackage{fullpage}
\RequirePackage[letterpaper, margin=2cm]{geometry}
\RequirePackage[utf8]{inputenc}
\RequirePackage[spanish]{babel}
\RequirePackage{epsfig}
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{epstopdf}
\RequirePackage{mathtools}
\RequirePackage[hidelinks]{hyperref}
\RequirePackage{graphicx}
\RequirePackage{minted}
\RequirePackage{color}
\RequirePackage{parskip}
\RequirePackage{caption}
\RequirePackage{subcaption}
\RequirePackage{ifthen}

% Font http://www.tug.dk/FontCatalogue/computermodernbright/
% Why? Because it is sans-serif, it is better for low-res screens
% Commented because there are some edge-cases and we don't want to handle them per-document basis.
% \usepackage{cmbright}
% \usepackage[T1]{fontenc}


% Default values

\parindent 0pt % No indentation paragraphs
\def\@evaluated{0} % By default, an activity is not evaluated


% Command definitions
\def\activitynumber#1{\def\@activitynumber{#1}}
\def\semester#1{\def\@semester{#1}}
\def\year#1{\def\@year{#1}}
\def\activitydate#1{\def\@activitydate{#1}}
\def\activitytitle#1{\def\@activitytitle{#1}}
\def\pushtime#1{\def\@pushtime{#1}}
\def\evaluated{\def\@evaluated{1}}
\def\formlink#1{\def\@formlink{#1}}

% Config to put titles and "entrega" sections automatically

\newcommand{\makepucheader}{
    \noindent\begin{tabular}{ll}
    \includegraphics[height=2.5cm]{puclogo.eps}
    &
    \begin{minipage}[b]{\textwidth}
    \noindent\textsc{Pontificia Universidad Católica de Chile\\
    Escuela de Ingeniería\\
    Departamento de Ciencia de la Computación\\
    IIC2233 --- Programación Avanzada \@year-\@semester\\    
    }
    \end{minipage}
    \end{tabular}
}

\newcommand{\makeactivitytitle}{
    \begin{flushright}
    \@activitydate~de~\@year\\
    \ifthenelse{\equal{\@evaluated}{1}}{\color{magenta}\textbf{Actividad Sumativa}}{\color{green}\textbf{Actividad Formativa}}
    \end{flushright}
    \begin{center}
    \ifthenelse{\equal{\@evaluated}{1}}{\textbf{\Huge Actividad Sumativa~\@activitynumber}}{\textbf{\Huge Actividad Formativa~\@activitynumber}}
    \\
    \vspace{2ex}
    \textbf{\Large \@activitytitle}
    \end{center}
}

\AtBeginDocument{
    \makepucheader
    \makeactivitytitle
}

\AtEndDocument{
    \section*{Entrega}
    \begin{itemize}
    	\item \textbf{Lugar:} En su repositorio privado de GitHub, en la \textbf{carpeta} \texttt{Actividades/AC\@activitynumber/}
    	\item  \textbf{Hora del \textit{push}:}~\@pushtime
    \end{itemize}
    \ifthenelse{\equal{\@evaluated}{1}}{}{
    \section*{Auto-evaluación}
    Como esta corresponde a una actividad formativa, te extendemos la instancia de responder, después de terminada la actividad, una auto-evaluación de tu desempeño. Esta se habilitará a las \textbf{16:50 de jueves \@activitydate} y tendrás plazo para responderla hasta las \textbf{23:59 del día siguiente}. Puedes acceder al formulario mediante el siguiente enlace:
    \begin{center}
        \url{\@formlink}
    \end{center}
    
    El asistir, realizar la actividad y responder la auto-evaluación otorgará como bonificación al alumno 2 décimas para sumar en su peor actividad sumativa del semestre.
        
    }
}

% Config to load images automatically from ''images'' folder

\graphicspath{ {images/} }

% Minted

\newminted[python]{python}{linenos,frame=single} % Use \begin{python}code\end{python}!
\newmintedfile[pythoninput]{python}{linenos,frame=single} % Use \pythoninput{file.py}!
\newcommand{\mil}[1]{\mintinline{python}{#1}}

% Comentarios entre ayudantes y profes

\definecolor{copper}{rgb}{0.72, 0.45, 0.2}
\definecolor{darkgreen}{rgb}{0.05, 0.6, 0.05}
\definecolor{purple}{rgb}{0.4,0.3,0.8}
\definecolor{darkorange}{rgb}{1.0, 0.55, 0.0}
\definecolor{wine}{rgb}{0.8, 0.4, 0.4}
\definecolor{azul-benja}{rgb}{0, 0, 1}
\definecolor{verdebienchillon}{rgb}{0.55, 0.74, 0.01}
\definecolor{negroni}{rgb}{0.85, 0.10, 0.01}
\definecolor{amber-ale}{rgb}{0.90, 0.45, 0.05}
\definecolor{indianyellow}{rgb}{0.89, 0.66, 0.34}
\definecolor{codegray}{rgb}{0.9,0.9,0.9}



\newcommand{\com}[3]{{\colorbox{#2}{\bfseries\sffamily\scriptsize\textcolor{white}{#1}}}
{\textcolor{#2}{\sf\small\textit{#3}}}}

% Si quiere crear su propio comando para hacer comentarios, hágalo acá

\newcommand{\ff}[1]{\com{fdoflorenzano}{magenta}{#1}}
\newcommand{\aaossa}[1]{\com{aaossa}{red}{#1}}
\newcommand{\cruz}[1]{\com{cruz}{darkorange}{#1}}

\newcommand{\enzo}[1]{\com{Enzo}{darkgreen}{#1}}
\newcommand{\dte}[1]{\com{Dante}{blue}{#1}}
\newcommand{\dan}[1]{\com{Dani}{verdebienchillon}{#1}}
\newcommand{\ben}[1]{\com{Benja}{azul-benja}}
\newcommand{\ay}[1]{\com{Ayudante}{cyan}{#1}}
