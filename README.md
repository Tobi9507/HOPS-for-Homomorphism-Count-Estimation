# HOPS-for-Homomorphism-Count-Estimation

Das Projekt kann durch Eingabe von "make" kompiliert werden. Mit "./demo [pattern.txt] [inputgraph.txt]" kann ein Testdurchlauf gestartet werden. Das Programm gibt die Ergebnisse der Algorithmen homHoPS, homHoPS+, HoPS und sGHD auf der übergebenen Eingabe über jeweils 60 Sekunden aus. Für Details zu Aufrufoptionen siehe weiter unten. Es wird der g++ Compiler(Version 9.4.0) verwendet. Wegen der eventuell sehr großen Zahlenwerte werden Datentypen und Funktionen der GMP-Library(Version 6.3.0) verwendet [https://gmplib.org/]. Eine Installation von Pyhton 3.8.3 mit matplotlib wird benötigt.

Für die Repräsentation der Graphen wird ein .txt Format verwendet. Die erste Zeile enthält die Anzahl der Knoten. Die darauf folgenden Zeilen beschreiben jeweils eine Kante: [NodeId#x] [NodeId#y] beschreibt eine Kante zwischen den Knoten mit den IDs x und y. Die Knoten IDs sind die Zahlen von 0 bis zu der Anzahl an Knoten minus 1.

Der Ordner "input" enthält die verwendeten Datensets. Das Datenset LiveJournal ist wegen seiner Größe nicht enthalten. Die Datensets sind ebenfalls im .gr Format vorhanden. Dieses Format wird von der Implementation des exakten Algorithmus verwendet [https://github.com/ChristianLebeda/HomSub].

##DETAILS AUFRUF
Ein Aufruf des Demoprogramm kann über mehrere Optionen gesteuert werden. Dazu muss die jeweilige Option an beliebiger Stelle nach den Eingabegraphen folgen. Eine Liste der verfügbaren Optionen:

"-homhops"
"-homhopsall"
"-hops"
"-sghd"
Durch diese Optionen können einzelne Algorithmen für die Berechnung ausgewählt werden. Wird keine dieser Optionen angegeben, werden die Lösungen für alle vier Algorithmen berechnet.

"-exacthom [Wert der exakten Lösung für Homomorphismen]" : Über diese Option kann dem Programm die exakte Lösung für Homomorphismen mitgeteilt werden. Dies ist notwendig für die Berechnung des relativen Fehlers und dem Anzeigen eines entsprechenden Plots.

"-exactiso [Wert der exakten Lösung für Isomorphismen]" : analog zu "-exacthom".

"-time [ganzzahlige Zeitangabe in Sekunden] : Über diese Option kann gesteuert werden, wie lange die Algorithmen jeweils laufen sollen. [Default=60]
