# Tahap 1: kompilasi
FROM gcc:13 AS build
WORKDIR /app
COPY main.cpp .
RUN g++ -std=c++17 -O2 -pthread main.cpp -o laporan

# Tahap 2: image kecil untuk dijalankan
FROM debian:bookworm-slim
WORKDIR /app
COPY --from=build /app/laporan .
COPY media ./media
ENV PORT=10000
EXPOSE 10000
CMD ["./laporan"]
