# Ksiazki
 A project to sort books by labels

Input file is Text.txt

Sample file content :

        Platon; Uczta; filozofia
        platon; Uczta; Filozofia
        Shakes,.,./.,/peare; Hamlet; tragedia, barok
        shakes,.,./.,/peare; Hamlet; tragedia, barok
        Cormen; Algorytmy; infor//./././matyka, podrecznik
        Mickiewicz; Pan Tadeusz; klas././.yka, ,,,,,,,,,,,,,,,,romantyzm, lektura
        Lem; Summa Technologiae; filo/././zofia, futu././rologia
        Mateu	sz;La	bu;F	i
        Ma,,,,,,,,,,,,,,ti;D#$%%$#upa;           ,,,,,,,,,,,,,,,,,,,,,,,,,,,Filozofia
        platon; Uczta; Filozofia
     
Output file is Etykiety.txt

Sample file content :

       etykieta to filozofia
       autor : Lem tytul :  Summa Technologiae	 autor : Mati tytul : Dupa	 autor : platon tytul :  Uczta	 autor : platon tytul :  Uczta	 autor : Platon tytul :  Uczta	


       etykieta to tragedia
       autor : shakespeare tytul :  Hamlet	 autor : Shakespeare tytul :  Hamlet	



A project to sort books by labels, the subsequent book titles are read from the Text.txt file. Full naming control has been implemented. 
If there is any additional special character in the middle of word it will be ignored and program won't take it 

