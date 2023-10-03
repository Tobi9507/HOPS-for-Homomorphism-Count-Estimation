# HOPS-for-Homomorphism-Count-Estimation

work in progress

Der Ordner "input" enthält die verwendeten Datensets. Das Datenset LiveJournal ist nicht enthalten.

Für die Datensets wird ein .txt Format verwendet. Die erste Zeile enthält die Anzahl der Knoten. Die darauf folgenden Zeilen beschreiben jeweils eine Kante: [NodeId#x] [NodeId#y] beschreibt eine Kante zwischen den Knoten mit den IDs x und y. Die Knoten IDs sind die Zahlen von 0 bis zu der Anzahl an Knoten-1. 

Die Datensets sind ebenfalls im .gr Format vorhanden. Dieses Format wird von der Implementation des exakten Algorithmus verwendet [https://github.com/ChristianLebeda/HomSub].
