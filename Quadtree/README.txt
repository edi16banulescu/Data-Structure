Pentru formarea quad-tree-ului am creat structura TheRealTree asemanatoare celei QuadTree
si structura RGB asociata matricei de pixeli.

Functia assign_vector creeaza arborele propriu zis din nodurile create recursiv in functia
uniform, iar functia copy_to_vector creeaza vectorul indexat conform cerintelor asociat 
Quad-tree-ului numit in programul meu TheRealTree.

In functia uniform creeam recursiv nodurile arborelui folosind formula pentru mean din
cerinta.

In functia de decompresie creeam matricea RGB de pixeli recursiv folosind vectorul indexat de
noduri creeat la functia anterioara.