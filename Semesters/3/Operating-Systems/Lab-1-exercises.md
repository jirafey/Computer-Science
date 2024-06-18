Oczywiście, oto poprawiony tekst w języku polskim:

1.10 Zadania do samodzielnego wykonania

1. Zbadaj szczegółowo działanie "podpowiadacza" nazw plików, który uaktywnia się, gdy podczas pisania polecenia użyjesz klawisza Tab; w tym celu przy użyciu polecenia `touch` załóż w dowolnym pustym katalogu pliki o poniższych nazwach:
   - aaa
   - aab
   - aac
   - aba
   - abb
   - abc
   A następnie będąc w tymże katalogu, napisz w linii poleceń `cat a` i naciśnij dwukrotnie klawisz Tab. Teraz dopisz literę 'a' lub 'b' i ponownie naciśnij klawisz Tab. Uważnie obserwuj zachowanie konsoli.

2. Przetestuj zachowanie opisane w poniższym fragmencie strony pomocy powłoki Bash:
   Uzupełnianie complete (TAB):
   Usiłuje przeprowadzić uzupełnianie tekstu przed punktem. Bash próbuje uzupełniania traktując tekst kolejno jako zmienną (jeżeli tekst zaczyna się od $), nazwę użytkownika (jeśli tekst zaczyna się od ~), nazwę hosta (jeśli tekst zaczyna się od @) lub polecenie (łącznie z aliasami i funkcjami). Jeżeli żadne z powyższych nie daje dopasowania, to próbowane jest uzupełnianie nazw plików.

3. Sprawdź, jaki efekt wywołują następujące postaci polecenia `cd`:
   - `cd .`
   - `cd ..`
   - `cd`
   - `cd -`

4. Zbadaj zachowanie poleceń `pushd` i `popd`.

5. Polecenie `history` powoduje wypisanie historii dotychczas wydanych poleceń. Każde z poleceń w historii opatrzone jest numerem. Wydanie polecenia `!n` (gdzie 'n' jest numerem jednego z poleceń w historii) powoduje ponowne wykonanie tego polecenia. Sprawdź, czy po wydaniu takiego polecenia numeracja w historii zmienia się.

6. Użyj dokumentu pomocy polecenia `ls`, aby odpowiedzieć na poniższe pytania:
   - Jak wypisać nazwy plików/katalogów w jednej kolumnie?
   - Jak posortować listę plików według ich rozmiaru?

7. Polecenie postaci `ls katalog` spowoduje wypisanie zawartości katalogu 'katalog'. Jak nakłonić polecenie `ls`, aby zamiast tego podało tylko informacje o katalogu 'katalog' bez wypisywania jego zawartości?

8. Czy możliwe jest istnienie w pewnym katalogu pliku i katalogu o takiej samej nazwie?

9. Załóż w swoim katalogu domowym następujące poddrzewo katalogów:
   ```
   ├── dira
   │   ├── diraa
   │   │   ├── diraaa
   │   │   └── diraab
   │   └── dirab
   │       ├── diraaa
   │       └── diraab
   └── dirab
       ├── diraaa
       └── diraab
   ```
   W każdym podkatalogu stwórz poleceniem `touch` jeden plik nazwany tak, jak ciąg znaków umieszczony po słowie 'dir' w nazwie katalogu (np. w katalogu 'dira' plik 'a'). Użyj tej struktury do przetrenowania następujących działań:
   - Skopiowania plików z 'dira/diraa/diraaa' do 'dira/diraa/diraab'
   - Przemianowania katalogu 'dira/dirab/dirabb' na 'fake'
   - Przeniesienia całej gałęzi zaczynającej się na katalogu 'dirab' do katalogu 'diraab'

10. Uwaga! Bądź ostrożny – to niebezpieczne! Jaki efekt wywołuje użycie polecenia `rm -rf *`?

11. Usuń całe drzewo katalogów z zadania 9. wraz z zawartością.

12. Sprawdź zachowanie poleceń `cp` i `mv` w sytuacji, gdy wywołano je z dwoma argumentami i drugi argument określa:
    - istniejący plik
    - istniejący katalog
    - nieistniejący plik/katalog

13. Sprawdź zachowanie poleceń `cp` i `mv` w sytuacji, gdy wywołano je z trzema argumentami, z których dwa pierwsze są nazwami istniejących plików, a trzeci:
    - jest nazwą istniejącego pliku
    - jest nazwą istniejącego katalogu
    - jest nazwą nieistniejącego pliku/katalogu



14. Jaki efekt wywołuje użycie opcji `-h` polecenia `ls`?

15. Polecenie `df` powoduje wypisanie informacji o wolnym miejscu na dyskach dostępnych w systemie. Użyj polecenia `watch`, aby co jedną sekundę wyświetlać bieżące dane o dostępnej pamięci dyskowej.

16. Co odróżnia od siebie dane prezentowane przez polecenia `w`, `who` i `finger`?

17. Zbadaj co zawiera i do jakich celów używany jest plik `~/.bash_history`? Jaki efekt wywoła usunięcie tego pliku?

18. Co zawiera plik `/proc/cpuinfo`?

19. Jaki efekt wywołuje opcja `-v` dodana do poleceń `cp`, `mv` i `rm`?

20. Spróbuj użyć polecenia `cat` do wypisania na ekranie zawartości pliku `/proc/kcore`. Wyjaśnij uzyskany efekt wiedząc, że plik ten (a dokładniej rzecz biorąc pseudoplik) odwzorowuje zawartość całej pamięci operacyjnej komputera i tym samym, daje dostęp do przestrzeni adresowej wszystkich obecnych w systemie procesów.
