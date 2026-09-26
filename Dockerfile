FROM python:3.14-slim
ENV PYTHONDONTWRITEBYTECODE=1 PYTHONUNBUFFERED=1
WORKDIR /app
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
COPY api_server.py ./
COPY decompiled/signature_algorithm.py decompiled/vm_program_ll_src2_exported.hex ./decompiled/
USER 1000:1000
CMD ["python", "-u", "api_server.py", "--host", "0.0.0.0", "--port", "31376", "--allow-unverified-sign", "--env-flags", "0x00"]
