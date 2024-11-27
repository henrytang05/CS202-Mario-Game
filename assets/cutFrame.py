from PIL import Image

# Mở sprite sheet
sprite_sheet = Image.open("assets/MarioLuigi.gif")

# Kích thước khung hình
frame_width = 500
frame_height = 8 * 5 + 3

# Tính số hàng và số cột
cols = sprite_sheet.width // frame_width
rows = sprite_sheet.height // frame_height

for row in range(rows):
    for col in range(cols):
        # Vị trí khung hình
        left = col * frame_width
        upper = row * frame_height
        right = left + frame_width
        lower = upper + frame_height

        # Cắt khung hình
        frame = sprite_sheet.crop((left, upper, right, lower))
        frame.save(f"frame_{row}_{col}.png")