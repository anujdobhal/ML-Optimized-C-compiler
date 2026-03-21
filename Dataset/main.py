#df = pd.read_csv(r"C:\Users\shali\Desktop\compiler\new_dataset.csv")

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

print("🚀 Training started...")

# -----------------------------
# 1. Load dataset
# -----------------------------
df = pd.read_csv(r"C:\Users\shali\Desktop\compiler\new_dataset.csv")


print("Original shape:", df.shape)

# -----------------------------
# 2. Remove duplicates
# -----------------------------
df = df.drop_duplicates()
print("After removing duplicates:", df.shape)

# -----------------------------
# 3. Handle rare classes
# -----------------------------
df["unroll_factor"] = df["unroll_factor"].replace({2:16, 8:16})

# -----------------------------
# 4. Features & Target
# -----------------------------
X = df[[
    "Depth",
    "TotalInstructions",
    "MemoryOperations",
    "BranchInstructions",
    "InputDeps"
]]

y = df["unroll_factor"]

# -----------------------------
# 5. Stratified Split
# -----------------------------
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# -----------------------------
# 6. Train Model
# -----------------------------
model = RandomForestClassifier(
    n_estimators=200,
    max_depth=5,
    min_samples_split=4,
    min_samples_leaf=2,
    class_weight='balanced',
    random_state=42
)

model.fit(X_train, y_train)

print("✅ Model trained")

# -----------------------------
# 7. Prediction
# -----------------------------
y_pred = model.predict(X_test)

# -----------------------------
# 8. Performance Metrics
# -----------------------------
accuracy = accuracy_score(y_test, y_pred)
print("\n🎯 Accuracy:", accuracy)

print("\n📊 Classification Report:\n")
print(classification_report(y_test, y_pred, zero_division=0))

print("\n🧮 Confusion Matrix:\n")
print(confusion_matrix(y_test, y_pred))

print("\n✅ DONE")