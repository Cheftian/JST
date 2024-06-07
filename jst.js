function runJST() {
    const kasus = document.getElementById('caseSelect').value;
    const berat = [
        parseFloat(document.getElementById('w1').value),
        parseFloat(document.getElementById('w2').value),
        parseFloat(document.getElementById('w3').value)
    ];
    const iterasi = parseInt(document.getElementById('iterations').value);
    const miu = 0.1;
    const input = [
        [1, 0, 0],
        [1, 0, 1],
        [1, 1, 0],
        [1, 1, 1]
    ];
    let target;

    if (kasus === "OR") {
        target = [0, 1, 1, 1];
    } else if (kasus === "AND") {
        target = [0, 0, 0, 1];
    } else if (kasus === "ANDNOT") {
        target = [0, 0, 1, 0];
    }

    let hasil = [0, 0, 0, 0];
    let status = [0, 0, 0, 0];
    let rumus = [0, 0, 0, 0];
    let selesai = false;
    let iter = 1;

    let resultHTML = `
        <table>
            <tr>
                <th>Iterasi ke-</th>
                <th>Target</th>
                <th>Hasil</th>
                <th>Rumus</th>
                <th>Status</th>
                <th>w1</th>
                <th>w2</th>
                <th>w3</th>
            </tr>
    `;

    while (iter <= iterasi && !selesai) {
        selesai = true;  // Asumsikan iterasi ini akan selesai
        for (let i = 0; i < 4; i++) {
            rumus[i] = 0;
            for (let j = 0; j < 3; j++) {
                rumus[i] += (input[i][j] * berat[j]);
            }

            hasil[i] = rumus[i] < -1e-3 ? 0 : 1;
            status[i] = target[i] - hasil[i];

            if (status[i] !== 0) {
                selesai = false;  // Ada yang diubah, jadi belum selesai
                for (let j = 0; j < 3; j++) {
                    berat[j] += miu * status[i] * input[i][j];
                }
            }

            resultHTML += `
                <tr>
                    <td>${iter}</td>
                    <td>${target[i]}</td>
                    <td>${hasil[i]}</td>
                    <td>${rumus[i].toFixed(1)}</td>
                    <td>${status[i]}</td>
                    <td>${berat[0].toFixed(1)}</td>
                    <td>${berat[1].toFixed(1)}</td>
                    <td>${berat[2].toFixed(1)}</td>
                </tr>
            `;
        }
        if (iter < iterasi && !selesai) {
            resultHTML += `
                <tr class="iterasi-separator"></tr>
            `;
        }
        iter++;
    }

    resultHTML += `</table>`;
    document.getElementById('result').innerHTML = resultHTML;
}
