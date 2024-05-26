let isJapanese = true; // Initial language set to Japanese

function toggleLanguage() {
    isJapanese = !isJapanese;
    document.getElementById('title').textContent = isJapanese ? 'LLMのSecurity 論文まとめ' : 'LLM Security Paper Summaries';
    document.getElementById('nav-attack').textContent = isJapanese ? '攻撃' : 'Attack';
    document.getElementById('nav-defense').textContent = isJapanese ? '防御' : 'Defense';
    document.getElementById('nav-vulnerability').textContent = isJapanese ? 'LLMの脆弱性調査' : 'LLM Vulnerability Research';
    document.getElementById('nav-datasets').textContent = isJapanese ? 'データセット' : 'Datasets';
    document.getElementById('sec-attack').textContent = isJapanese ? '攻撃' : 'Attack Methods';
    document.getElementById('sub-attack-prompt').textContent = isJapanese ? 'プロンプトインジェクション' : 'Prompt Injection';
    document.getElementById('sub-attack-backdoor').textContent = isJapanese ? 'バックドア' : 'Backdoors';
    document.getElementById('sub-attack-jailbreak').textContent = isJapanese ? 'ジェイルブレイク' : 'Jailbreak';
    document.getElementById('sec-defense').textContent = isJapanese ? '防御' : 'Defense';
    document.getElementById('secvulnerability').textContent = isJapanese ? 'LLMの脆弱性調査' : 'LLM Vulnerability Research';
    document.getElementById('sec-datasets').textContent = isJapanese ? 'データセット' : 'Datasets';
}

