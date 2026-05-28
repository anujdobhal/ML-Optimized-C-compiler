import pandas as pd
import numpy as np
df = pd.read_csv("new_dataset.csv")
print("Original size:", len(df))
target_size = 500
new_rows = []
while len(df) + len(new_rows) < target_size:
    row = df.sample(n=1).iloc[0].copy()
    # Add small noise to features (except target)
    for col in df.columns[:-1]:  # all except unroll_factor
        noise = np.random.randint(-2, 3)  # small variation
        row[col] = max(1, row[col] + noise)  # avoid negative

    new_rows.append(row)

df_new = pd.DataFrame(new_rows)

df_final = pd.concat([df, df_new], ignore_index=True)

print("New size:", len(df_final))

# Save
df_final.to_csv("expanded_dataset.csv", index=False)

print("Expanded dataset saved!")