import java.io.File;
import java.util.Date;
import java.util.Scanner;

class LastModified {
	private static final long FIVE_SECONDS = 5000L;

	public static void main(String[] args) throws Exception {
		if (args.length == 0) {
			println("Filename not provided.\nusage: java LastModified <filename>");
			return;
		}

		var file = new File(args[0]);

		long previousLastModified = file.lastModified();
		while(true) {
			var lastModified = file.lastModified();
			println("Last modified in: " + new Date(lastModified));
			if (lastModified - previousLastModified > FIVE_SECONDS) {
				previousLastModified = lastModified;
				Scanner sc = new Scanner(file);
				while (sc.hasNextLine()) {
					String line = sc.nextLine();
					println(line);
					if (line.equals("EXIT")) return;
				}
			}
			Thread.sleep(1000);
		}
	}

	private static final void println(Object o) {
		System.out.println(o);
	}
}

