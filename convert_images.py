
from pathlib import Path
from PIL import Image

input_dir = Path("output/ppm")
output_dir = Path("output/png")

output_dir.mkdir(parents=True, exist_ok=True)

ppm_files = list(input_dir.glob("*.ppm"))

if not ppm_files:
    print("No PPM files found.")
else:
    for ppm_file in ppm_files:
        try:
            with Image.open(ppm_file) as image:
                image.convert("RGB").save(
                    output_dir / f"{ppm_file.stem}.png",
                    format="PNG"
                )

            print(f"Converted: {ppm_file.name}")

        except Exception as error:
            print(f"Failed: {ppm_file.name} - {error}")

    print("\nConversion completed.")
