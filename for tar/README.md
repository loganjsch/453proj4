# CSC 453 - Project 4 
Logan Schwarz, Kenneth Choi, Cole Turner

For our TinyFS implementation, we decided to go with structs for the various blocks.
While we were not able to complete the full implementation due to studying for the final exam and other efinals, we believe that our method was the right 
direction as each of the blocks have their own unique structure, with their headers beign the same (magic number & block type).

The repeated structure of a BlockHeader header was best implement as it's own structure called upon in each of our block types.

We also decided that a linked list structure would be the best method to maintain free blocks as it would be easy to insert and remove nodes quickly. 
Furthermore, it would be easy to traverse between the free blocks. This may slow down operations such as large traversals, but for our sake, simplicity of implementation and the scope of our FS the linked list provided more benefit.a

Our philosophy for the error codes was as follows:
We chose the 9 most likely error codes to be raised, for exampe bad arg being most likely, and corrupt errors being least likely. (Given a working system)
Based on order or likelihood we put the codes. There's no technical reason behind this ordering but the logic we thought made sense.


Notes on areas of improvement:
- tests for libDisk work 
- implementation for TinyFS will not work 
