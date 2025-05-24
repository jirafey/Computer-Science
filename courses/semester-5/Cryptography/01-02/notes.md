Pytanie 1: Czy wszystkie wartości skrótów SHA512 dla różnych plików maja tą samą
długość?
- Tak.

Pytanie 2: Czy dla różnych plików zawsze uzyskuje się różne wartości skrótów
obliczone za pomocą funkcji skrótu MD5 lub SHA512? Odpowiedź uzasadnij.
- Tak... jeżeli pliki mają inną zawartość. Jakakolwiek różnica w pliku (bitowa) wpłynie na zmianę wartości skrótu.

Pytanie 3: Czy funkcja skrótu SHA512 jest lepsza od funkcji MD5? Odpowiedź
uzasadnij.
- Jest lepsza, gdyż md5 dla innych plików może wygenerować ten sam `hash value`
sha512 generuje 64 bajtową wartość skrótu, a md5 tylko 16 bajtową.
md5 jest po po prostu przestarzały i nie jest nawet uważany za bezpieczną kryptograficzną funkcję haszującą.

Pytanie 4: Jakie czynności należy wykonać, aby odtworzyć wiadomość, jeśli w poczcie
elektronicznej otrzymasz tajną wiadomość i wiadomość ta została zaszyfrowana za
pomocą polecenia typu “gpg --symmetric --armor message.txt”?

- Należy użyć `gpg --armor -d file1.txt.asc` ponieważ flaga `-d` jest do dekrypcji.
