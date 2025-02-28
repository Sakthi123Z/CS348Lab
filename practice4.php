<!DOCTYPE html>
<html>
<head>
    <title>Multiplication Table</title>
    <style>
        table { border-collapse : collapse ; width : 50%; }
        th, td { border:1px solid black ; padding: 8px; text-align:center; }
    </style>
</head>
<body>
    <h2>Multiplication Table</h2>
    <form method="post">
        <label>Plese Type num ... :</label>
        <input type="number" name="num" required>
        <button type="submit">Generate</button>
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $num = intval($_POST["num"]);
        echo "<h3>Multiplication Table for $num</h3>";
        echo "<table>";
        echo "<tr><th>*</th>";
        for ($i = 1 ; $i <= $num ; $i++) {
            echo "<th>$i</th>";
        }
        echo "</tr>";
        for ($i = 1; $i <= $num; $i++) {
            echo "<tr><th>$i</th>";
            for ($j = 1; $j <= $num; $j++) {
                echo "<td>" . ($i * $j) . "</td>";
            }
            echo "</tr>";
        }
        echo "</table>";
    }
    ?>
</body>
</html>
