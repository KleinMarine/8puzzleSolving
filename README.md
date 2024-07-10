8-Puzzle問題解法
=============
### Goal：<br> ###
移動拼圖的空白格， <br>
最終目標為 {0 1 2 3 4 5 6 7 8}，<br>

輸入0為空白格，<br>
三種範例輸出以及輸入。

<hr>

範例一

### Input：<br> ###
<pre><code>{0 1 2 3 4 5 6 7 8}</code></pre>

### Output：<br> ###
<pre><code>It is the goal state.</code></pre>

<hr>

範例二

### Input：<br> ###
<pre><code>{0 1 2 3 4 5 6 8 7}</code></pre>

### Output：<br> ###
<pre><code>No solution!!</code></pre>


<hr>

範例三

### Input：<br> ###
<pre><code>{6 3 5 1 2 4 0 7 8}</code></pre>

### Output：<br> ###
<pre><code>move blank to right
move blank to up
move blank to left
move blank to up
move blank to right
move blank to down
move blank to down
move blank to left
move blank to up
move blank to up
move blank to right
move blank to down
move blank to right
move blank to up
move blank to left
move blank to left</code></pre>
