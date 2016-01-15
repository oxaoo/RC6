# RC6
The symmetric block cryptographic algorithm RC6.

### Algorithm of extension of a key:
#### On an input:
- b-byte the key set by the user, beforehand transformed to an array words L [0..., with-1];  
- r — quantity of rounds.  

#### On an output:
- w-bit table of keys of S[0..., 2r+3].  

```c
	S[0]=Pw
	for i=1 to 2r+3 do
    		S[i]=S[i-1]+Qw
 
	A=B=i=j=0

	v=3*max{c,2r+4}
	for s=1 to v do
    	{
        	    A=S[i]=(S[i]+A+B)<<<3
        	    B=L[j]=(L[j]+A+B)<<<(A+B)
        	    i=(i+1) mod (2r+4)
        	    j=(j+1) mod c
    	}
```

<br>
### Encryption algorithm:
RC6 works with four w-bit registers A, B, C and D which contain an input source text.  
#### On an input:
- r quantity of rounds;
- w-bit keys for each round of S[0, …, 2r + 3].  

#### On an output:
- the ciphertext remains in A, B, C and the D output ciphertext at the end of encoding.  

```c
	B = B + S[0]
	D = D + S[1]
	for i = 1 to r do
	{
		t = (B(2B + 1)) <<< lg w
		u = (D(2D + 1)) <<< lg w
		A = ((A ⊕ t) <<< u) + S[2i]
		C = ((C ⊕ u) <<< t) + S[2i + 1] 
    (A, B, C, D)  =  (B, C, D, A)
 
	}
	A = A + S[2r + 2]
	C = C + S[2r + 3]
```

<br>
### Algorithm of decoding:
#### On an input:
- the ciphertext saved in A, B, C and D;
- r quantity of rounds;
- w-bit keys for each round of S[0, …, 2r + 3].

#### On an output:
- a source text remains in A, B, C and D.

```c
	C = C - S[2r + 3]
	A = A - S[2r + 2]
 
	for i = r downto 1 do
	{
	   	 (A, B, C, D) = (D, A, B, C)
	   	 u = (D(2D + 1)) <<< lg w
	    	 t = (B(2B + 1)) <<< lg w
	   	 C = ((C - S[2i + 1]) >>> t) ⊕ u
	   	 A = ((A - S[2i]) >>> u) ⊕ t
	}
	D = D - S[1]
	B = B - S[0]
```
