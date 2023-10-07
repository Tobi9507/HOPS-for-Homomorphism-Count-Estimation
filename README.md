# HOPS-for-Homomorphism-Count-Estimation

Das Projekt kann durch Eingabe von "make" kompiliert werden. Mit "./demo [pattern.txt] [inputgraph.txt]" kann ein Testdurchlauf gestartet werden. Das Programm gibt die Ergebnisse der Algorithmen homHoPS, homHoPS+, HoPS und sGHD auf der übergebenen Eingabe über jeweils 60 Sekunden aus.  Es wird der g++ Compiler(Version 9.4.0) verwendet. Wegen der eventuell sehr großen Zahlenwerte werden Datentypen und Funktionen der GMP-Library(Version 6.3.0) verwendet [https://gmplib.org/].

Der Ordner "input" enthält die verwendeten Datensets. Das Datenset LiveJournal ist wegen seiner Größe nicht enthalten. Für die Datensets wird ein .txt Format verwendet. Die erste Zeile enthält die Anzahl der Knoten. Die darauf folgenden Zeilen beschreiben jeweils eine Kante: [NodeId#x] [NodeId#y] beschreibt eine Kante zwischen den Knoten mit den IDs x und y. Die Knoten IDs sind die Zahlen von 0 bis zu der Anzahl an Knoten minus 1. Die Datensets sind ebenfalls im .gr Format vorhanden. Dieses Format wird von der Implementation des exakten Algorithmus verwendet [https://github.com/ChristianLebeda/HomSub].

work in progress
- relative error
- plots
- manual time and repetitions
- manual algorithm exclusion
