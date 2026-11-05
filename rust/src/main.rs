fn main() {
    println!("三目並べゲームを開始します！");
    loop {
        playGame();
        if (retry()) {
            break;
        }
    }
}
