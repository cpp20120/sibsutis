#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Graphics/Renderer.h"

void Application::RenderBoard() {
  Renderer::ClearScreen({0.0f, 0.0f, 0.0f, 1.0f});

  FramebufferSpecification spec = m_ChessViewport->GetSpecification();
  if ((float)spec.Width != m_ChessViewportSize.x ||
      (float)spec.Height != m_ChessViewportSize.y) {
    m_ChessViewport->Resize((uint32_t)m_ChessViewportSize.x,
                            (uint32_t)m_ChessViewportSize.y);

    constexpr float temp = 4.5f;

    float aspectRatio = m_ChessViewportSize.x / m_ChessViewportSize.y;

    if (aspectRatio <= 1.0f)
      Renderer::UpdateProjectionMatrix(
          glm::ortho(-temp, temp, -temp / aspectRatio, temp / aspectRatio));
    else
      Renderer::UpdateProjectionMatrix(
          glm::ortho(-temp * aspectRatio, temp * aspectRatio, -temp, temp));

    m_CoordinateTransform = glm::inverse(Renderer::GetProjectionMatrix());
    m_CoordinateTransform = glm::scale(
        m_CoordinateTransform, {1 / (m_ChessViewportSize.x * 0.5f),
                                1 / (m_ChessViewportSize.y * -0.5f), 1.0f});
    m_CoordinateTransform = glm::translate(
        m_CoordinateTransform,
        {m_ChessViewportSize.x * -0.5f, m_ChessViewportSize.y * -0.5f, 0.0f});
  }

  m_ChessViewport->Bind();
  Renderer::ClearScreen(m_BackgroundColour);

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      const glm::vec4 colour =
          (x + y) % 2 == 0 ? m_LightSquareColour : m_DarkSquareColour;
      Renderer::DrawRect({-3.5f + x, 3.5f - y, 0.0f}, {1.0f, 1.0f}, colour);
    }
  }

  for (BitBoard legalMoves = m_LegalMoves; legalMoves;
       legalMoves &= legalMoves - 1) {
    Square square = GetSquare(legalMoves);
    int rank = RankOf(square);
    int file = FileOf(square);
    Renderer::DrawRect({-3.5f + file, -3.5f + rank, 0.0f}, {1.0f, 1.0f},
                       m_LegalMoveColour);
  }

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      std::shared_ptr<SubTexture> piece = GetChessSprite(m_Board[y * 8 + x]);

      if (piece && (y * 8 + x) != m_SelectedPiece)
        Renderer::DrawRect({-3.5f + x, -3.5f + y, 0.0f}, {1.0f, 1.0f}, piece);
    }
  }

  if (m_SelectedPiece != INVALID_SQUARE)
    Renderer::DrawRect({m_BoardMousePosition.x, m_BoardMousePosition.y, 0.5f},
                       {1, 1}, GetChessSprite(m_Board[m_SelectedPiece]));

  Renderer::Flush();

  m_ChessViewport->Unbind();
}

void Application::RenderChessPanel() {
  RenderBoard();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});
  ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, {400.f, 400.f});
  ImGui::Begin("Chessboard");

  auto [offsetX, offsetY] = ImGui::GetCursorPos();

  ImVec2 viewportSize = ImGui::GetContentRegionAvail();
  m_ChessViewportSize = {viewportSize.x, viewportSize.y};

  ImTextureID texture = (void*)(intptr_t)m_ChessViewport->GetColourAttachment();
  int framePadding = 0;
  ImVec4 backgroundColour = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  ImVec4 tintColour = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  ImGui::ImageButton(texture, viewportSize, {0, 1}, {1, 0}, framePadding,
                     backgroundColour, tintColour);

  auto [mouseX, mouseY] = ImGui::GetMousePos();
  auto [windowX, windowY] = ImGui::GetWindowPos();
  glm::vec2 mousePosition = {mouseX, mouseY};
  glm::vec2 viewportPosition = {windowX + offsetX, windowY + offsetY};
  glm::vec2 relativeMousePos = mousePosition - viewportPosition;

  m_BoardMousePosition =
      m_CoordinateTransform *
      glm::vec4{relativeMousePos.x, relativeMousePos.y, 1.0f, 1.0f};

  ImGui::End();

  ImGui::PopStyleVar(2);
}
